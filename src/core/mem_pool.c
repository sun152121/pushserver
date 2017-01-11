#include "mem_pool.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

mempool_t* create_mempool(int item_max_size, int alloc_now) {
	mempool_t* pool = malloc(sizeof(mempool_t));
	int i;
	int j;
	memblock_head_t* pool_head;
	memblock_t* block;

	for (i = 1; i <= MXAX_HEAD_SIZE; i++) {
		pool_head = &pool->head[i-1];

		pthread_mutex_init(&pool_head->mutex,NULL);
		pool_head->free = NULL;
		pool_head->max_count = item_max_size / (i * ALIGN_SIZE);
		pool_head->free_count = 0;

		if (alloc_now) {
			for (j = 0; j < pool_head->max_count; j++) {
				block = malloc(i * ALIGN_SIZE);
				block->next = pool_head->free;
				pool_head->free = block;
				pool_head->free_count++;
			}
		}
		
	}//for

	return pool;
}

void destry_mempool(mempool_t* pool) {
	int i;
	memblock_head_t* pool_head;
	memblock_t* block;

	for (i = 1; i <= MXAX_HEAD_SIZE; i++) {
		pool_head = &pool->head[i - 1];

		memblock_t* pBlock = pool_head->free;
		while (pBlock) {
			block = pBlock;
			pBlock = block->next;
			short* tag = (short*)block->ptr;
			free(block);
			block = NULL;
		}
	}

	free(pool);
	pool = NULL;
}

void* palloc(mempool_t* pool, int size, int zero) {
	int real_size = alignment(size + sizeof(short),ALIGN_SIZE);
	short index = real_size / ALIGN_SIZE;
	memblock_head_t* pool_head = &pool->head[index - 1];
	memblock_t* block;
	void* ptr;

	if (real_size > POOL_BLOCK_SIZE) {
		ptr = malloc(size);
		if (zero) {
			memset(ptr, 0, size);
		}

		return ptr;
	}

	pthread_mutex_lock(&pool_head->mutex);
	if (pool_head->free_count > 0) {
		block = pool_head->free;
		pool_head->free = block->next;
		pool_head->free_count--;
		pthread_mutex_unlock(&pool_head->mutex);
	}
	else {
		pthread_mutex_unlock(&pool_head->mutex);
		block = malloc(index * ALIGN_SIZE);
	}
	

	short* tag = (short*)block->ptr;
	*tag = index;

	ptr = block->ptr + sizeof(short);
	if (zero) {
		memset(ptr,0,size);
	}

	return ptr;
}

void* p_malloc(mempool_t* pool, int size) {
	return palloc(pool,size,0);
}

void* p_calloc(mempool_t* pool, int size) {
	return palloc(pool,size,1);
}

void p_free(mempool_t* pool,void* ptr) {
	if (ptr == NULL)
		return;

	short* tag = (short*)((uintptr_t)ptr - sizeof(short));
	assert(*tag > 0 && *tag < MXAX_HEAD_SIZE);

	memblock_t* block = (memblock_t*)tag;
	memblock_head_t* pool_head = &pool->head[*tag - 1];

	int size = 1;

	if ((*tag) * ALIGN_SIZE > POOL_BLOCK_SIZE) {
		free(ptr);
		return;
	}

	pthread_mutex_lock(&pool_head->mutex);
	if (pool_head->free_count < pool_head->max_count) {
		block->next = pool_head->free;
		pool_head->free = block;
		pool_head->free_count++;
		pthread_mutex_unlock(&pool_head->mutex);
	}
	else {
		pthread_mutex_unlock(&pool_head->mutex);
		free(block);
		block = NULL;
	}
	
}