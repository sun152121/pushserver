#ifndef MEM_CHAIN_H
#define MEM_CHAIN_H

#define IS_CHAIN_DATA_BLOCK_FULL(d) (d->end - d->last < ALIGN_SIZE £¿1:0)

typedef struct mem_chain_data_s mem_chain_data_t;
typedef struct mem_chain_data_large_s mem_chain_data_large_t;

struct mem_chain_data_large_s {
	mem_chain_data_large_t* next;
	void*	alloc;
};

struct mem_chain_data_s {
	char* last;
	char* end;
	mem_chain_data_t* next;
	int failed;
	unsigned full : 1;
};

typedef struct {
	mem_chain_data_t* start;
	mem_chain_data_t* current;
	mem_chain_data_large_t* large;
	int max;
}mem_chain_t;

mem_chain_t* create_mem_chain(int size);
void destroy_mem_chain(mem_chain_t* chain);
void reset_mem_chain(mem_chain_t* chain);
void* chain_alloc(mem_chain_t* chain,int size,int zero);
void* chain_malloc(mem_chain_t* chain,int size);
void* chain_calloc(mem_chain_t* chain,int size);
int chain_free(mem_chain_t* chain,void* p);

#endif