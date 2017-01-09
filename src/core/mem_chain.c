#include "mem_chain.h"
#include "mem_pool.h"

#include <stdlib.h>
#include <string.h>

static void* chain_alloc_small(mem_chain_t* chain, int align_size);
static void* chain_alloc_large(mem_chain_t* chain, int align_size);

mem_chain_t* create_mem_chain(int size) {
	mem_chain_t* chain = malloc(sizeof(mem_chain_t));
	int align_size = alignment(size, ALIGN_SIZE);
	mem_chain_data_t* d = malloc(align_size);

	d->last = (char *)d + sizeof(mem_chain_data_t);
	d->end = (char *)d + align_size;
	d->next = NULL;
	d->failed = 0;
	
	/* 内存小于最小对齐值(ALIGN_SIZE)认为此块内存已经满了，内存分配的时候直接跳过此内存块的查找 */
	d->full = 0;		

	chain->start = d;
	chain->current = d;
	chain->large = NULL;
	chain->max = align_size - sizeof(mem_chain_data_t);
	
	return chain;
}

void destroy_mem_chain(mem_chain_t* chain) {
	mem_chain_data_large_t* l;
	mem_chain_data_t* d;
	
	//释放大内存
	for (l = chain->large; l; l = l->next) {
		if (l->alloc) {
			free(l->alloc);
		}
		free(l);
	}

	//释放内存链
	for (d = chain->start; d; d = d->next) {
		free(d);
	}

	free(chain);
}

void reset_mem_chain(mem_chain_t* chain) {
	mem_chain_data_large_t* l;
	mem_chain_data_t* d;

	//释放大内存
	for (l = chain->large; l; l = l->next) {
		if (l->alloc) {
			free(l->alloc);
		}
		free(l);
	}

	chain->large = NULL;
	chain->current = chain->start;

	//内存链指针归位
	for (d = chain->start; d; d = d->next) {
		d->last = (char *)d + sizeof(mem_chain_data_t);
		d->failed = 0;
		d->full = 0;
	}
}

void* chain_alloc(mem_chain_t* chain, int size, int zero) {
	int align_size = alignment(size, ALIGN_SIZE);
	void* p;
	
	if (align_size > chain->max) {
		p = chain_alloc_large(chain,align_size);
	}
	else {
		p = chain_alloc_small(chain,align_size);
	}

	if (zero) {
		memset(p, 0, align_size);
	}

	return p;
}

//小内存分配
static void* chain_alloc_small(mem_chain_t* chain,int align_size) {
	mem_chain_data_t* d;
	mem_chain_data_t* new_d;
	char* m;

	for (d = chain->current; d->next; d = d->next) {
		if (d->full || d->failed > 4) {
			chain->current = d->next;
			continue;
		}
		if (d->last + align_size > d->last) {
			d->failed++;
		}
		else {
			m = d->last;
			d->last += align_size;

			if (d->end - d->last < ALIGN_SIZE) {
				d->full = 1;
			}

			return m;
		}
	}

	//内存分配失败，新增内存链
	int chain_data_block_size = (int)(chain->start->end - (char*)chain->start);
	new_d = (mem_chain_data_t*)malloc(chain_data_block_size);
	if (new_d == NULL) {
		return NULL;
	}

	m = (char*)new_d;
	
	new_d->end = m + chain_data_block_size;
	new_d->failed = 0;
	new_d->full = 0;
	new_d->next = NULL;

	m += sizeof(mem_chain_data_t);
	new_d->last = m + align_size;

	d->next = new_d;

	return m;
}

//大内存分配
static void* chain_alloc_large(mem_chain_t* chain,int align_size) {
	mem_chain_data_large_t* l;
	void* p;
	int n;

	p = malloc(align_size);

	for (l = chain->large; l; l = l->next) {
		if (l->alloc) {
			l->alloc = p;
			return p;
		}

		if (n++ > 3) {
			break;
		}
	}

	l = chain_alloc_small(chain,alignment( sizeof(mem_chain_data_large_t), ALIGN_SIZE) );
	if (l == NULL) {
		free(p);
		return NULL;
	}

	l->alloc = p;
	l->next = chain->large;
	chain->large = l;

	return p;
}

void* chain_malloc(mem_chain_t* chain, int size) {
	return chain_alloc(chain,size,0);
}

void* chain_calloc(mem_chain_t* chain, int size) {
	return chain_alloc(chain, size, 1);
}

int chain_free(mem_chain_t* chain, void* p) {
	mem_chain_data_large_t* l;

	for (l = chain->large; l; l = l->next) {
		if (p == l->alloc) {
			free(l->alloc);
			l->alloc = NULL;

			return 0;
		}
	}

	return -1;
}