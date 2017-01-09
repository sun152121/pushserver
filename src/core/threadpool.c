#include <stdio.h>
#include <unistd.h>

#include "threadpool.h"
#include "event.h"

threadpool_t *create_threadpool(mempool_t *pool, int thread_count, thread_fun_pt fun,task_queue_t *task_queue) {
	int i;
	int iRet;
	pthread_t *threads;
	pthread_attr_t attr;

	threadpool_t *threadpool = pmalloc(pool,sizeof(threadpool_t));
	if (threadpool == NULL) {
		return NULL;
	}

	threads = pmalloc(pool, thread_count * sizeof(pthread_t));
	if (threads == NULL) {
		pfree(pool,threadpool);
		return NULL;
	}

	threadpool->pool = pool;
	threadpool->threads = threads;
	threadpool->task_queue = task_queue;
	threadpool->status = 0;
	threadpool->start = thread_start;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	for (i = 0; i < thread_count; i++) {
		iRet = pthread_create(&threads[i],&attr, fun, threadpool);
		if (iRet) {
			printf("pthread_create fail!\n");

			pfree(pool, threadpool);
			pfree(pool, threads);
			return NULL;
		}
	}

	return threadpool;
}

void *thread_fun(void *arg) {
	threadpool_t *threadpool = arg;
	mempool_t *pool = threadpool->pool;
	int status = threadpool->status;
	task_t *task;
	event_t *ev;

	while (1) {
		if (status == 0) {
			sleep(1);
			continue;
		}
		task = pop_task(threadpool->task_queue);
		ev = task->data;

		ev->handler(ev);

		//pfree(pool,ev);
		pfree(pool,task);
	}
}

void thread_start(void *arg) {
	threadpool_t *threadpool = arg;
	
	threadpool->status = 1;
}