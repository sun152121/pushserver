#include <stdlib.h>

#include "task_queue.h"

task_queue_t *create_task_queue(mempool_t *pool) {
	//task_queue_t *queue = pmalloc(pool,sizeof(task_queue_t));
	task_queue_t *queue = malloc(sizeof(task_queue_t));
	if (queue == NULL) {
		return NULL;
	}

	queue->pool = pool;
	pthread_mutex_init(&queue->mutex, NULL);
	pthread_cond_init(&queue->cond, NULL);

	queue_init(&queue->task.queue);

	return queue;
}

void destroy_task_queue(task_queue_t *task_queue) {
#if 0
	mempool_t *pool = task_queue->pool;
	pfree(pool, task_queue);
#endif
	free(task_queue);
}

void push_task(task_queue_t *task_queue, task_t *task) {
	pthread_mutex_lock(&task_queue->mutex);
	queue_insert_tail(&task_queue->task.queue,&task->queue);
	pthread_cond_signal(&task_queue->cond);
	pthread_mutex_unlock(&task_queue->mutex);
}

task_t *pop_task(task_queue_t *task_queue) {
	queue_t *q;

	pthread_mutex_lock(&task_queue->mutex);
	while (queue_empty(&task_queue->task.queue)) {
		pthread_cond_wait(&task_queue->cond,&task_queue->mutex);
	}
	q = queue_head(&task_queue->task.queue);
	queue_remove(q);
	pthread_mutex_unlock(&task_queue->mutex);

	return queue_data(q,task_t,queue);
}