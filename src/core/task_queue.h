#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include <pthread.h>

#include "mem_pool.h"
#include "queue.h"

typedef struct task_s {
	void *data;
	queue_t queue;
} task_t;

typedef struct task_queue_s
{
	mempool_t *pool;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	task_t task;
} task_queue_t ;

task_queue_t *create_task_queue(mempool_t *pool);
void destroy_task_queue(task_queue_t *task_queue);
void push_task(task_queue_t *task_queue,task_t *task);
task_t *pop_task(task_queue_t *task_queue);

#endif // !TASK_QUEUE_H