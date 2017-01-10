#ifndef MEMPOOL_H
#define MEMPOOL_H

#include <pthread.h>

#if 0
#define pmalloc(pool,size) malloc(size)
#define pcalloc (pool,size) calloc(size)

#define pfree(pool,ptr)	 free(ptr)
#else

#define pmalloc(pool,size) p_malloc(pool,size)
#define pcalloc (pool,size) p_calloc(pool,size)

#define pfree(pool,ptr)	 p_free(pool,ptr)

#endif

//�ڴ�ع��������ڴ��4KB
#define POOL_BLOCK_SIZE	4 * 1024
#define MXAX_HEAD_SIZE (POOL_BLOCK_SIZE >> 3)
//ÿ��item�����128KB
#define POOL_BLOCK_DEFAULT_TOTAL_SIZE	128 * 1024

//8�ֽڶ���
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
void* p_malloc(mempool_t* pool,int size);
void* p_calloc(mempool_t* pool,int size);
void p_free(mempool_t* pool,void* ptr);

#endif