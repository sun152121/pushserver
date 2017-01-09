#ifndef MEMPOOL_H
#define MEMPOOL_H

#include <pthread.h>

//内存池管理最大的内存块4KB
#define POOL_BLOCK_SIZE	4 * 1024
#define MXAX_HEAD_SIZE (POOL_BLOCK_SIZE >> 3)
//每个item最大是128KB
#define POOL_BLOCK_DEFAULT_TOTAL_SIZE	128 * 1024

//8字节对齐
#define ALIGN_SIZE 8
#define alignment(a,n) \
    ((a + n - 1) & (~(n - 1)))

union memblock_s;
typedef union memblock_s memblock_t;

union memblock_s {
	memblock_t* next;
	char ptr[0];
};

typedef struct memblock_head_s {
	pthread_mutex_t mutex;
	memblock_t* free;
	int max_count;
	int free_count;
}memblock_head_t;

typedef struct mempool_s {
	memblock_head_t head[MXAX_HEAD_SIZE];
} mempool_t;

mempool_t* create_mempool(int item_max_size,int alloc_now);
void destry_mempool(mempool_t* pool);
void* palloc(mempool_t* pool, int size,int zero);
void* pmalloc(mempool_t* pool,int size);
void* pcalloc(mempool_t* pool,int size);
void pfree(mempool_t* pool,void* ptr);

#endif