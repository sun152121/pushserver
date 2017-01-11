#ifndef EVENT_H
#define EVENT_H

#include <sys/epoll.h>

#include "mem_pool.h"
#include "task_queue.h"

#define EVENT_SIZE  1024

struct event_s;

typedef struct event_s event_t;

typedef void(*event_handler_pt)(event_t *ev);

struct event_s {
	int fd;
	void *data;
	event_handler_pt handler;
	int events;
} ;

typedef struct event_base_s {
	mempool_t *pool;
	int epfd;
	struct epoll_event *event;		/* event[] - events that were triggered */
	int nevent;
	task_queue_t *task_queue;
} event_base_t;

event_base_t *create_event_base(mempool_t *pool,int size,task_queue_t *task_queue);
void destroy_event_base(event_base_t *base);
int event_add_in(event_base_t *base, event_t *ev);
int event_add_out(event_base_t *base, event_t *ev);
int event_del_in(event_base_t *base, event_t *ev);
int event_del_out(event_base_t *base, event_t *ev);
int event_del(event_base_t *base, event_t *ev);

int event_wait(event_base_t *base,int timeout);
void event_dispatch(event_base_t *base);

#endif // !EVENT_H