#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "mem_pool.h"
#include "task_queue.h"

typedef struct threadpool_s threadpool_t;
typedef void *(*thread_fun_pt)(void *arg);

struct threadpool_s
{
	mempool_t *pool;
	int thread_count;
	pthread_t *threads;
	task_queue_t *task_queue;
	int status;

	void (*start)(void *arg);
};

threadpool_t *create_threadpool(mempool_t *pool,int thread_count, thread_fun_pt fun, task_queue_t *task_queue);
void *thread_fun(void *arg);
void thread_start(void *arg);

#endif // !THREADPOOL_H