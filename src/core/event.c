#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "event.h"
#include "contex.h"
#include "connection.h"

event_base_t *create_event_base(mempool_t *pool, int size,task_queue_t *task_queue) {
	event_base_t *base;
	int ep;
	struct epoll_event *event;

	ep = epoll_create(size);
	if (ep < 0) {
		return NULL;
	}

	event = pmalloc(pool,size * sizeof(*event));
	if (event == NULL) {
		close(ep);
		return NULL;
	}

	base = pmalloc(pool,sizeof(event_base_t));
	if (base == NULL) {
		pfree(pool,event);
		close(ep);
		return NULL;
	}

#if 0
	task_queue_t *task_queue = create_task_queue(pool);
	if (task_queue == NULL) {
		pfree(pool,event);
		close(ep);
		return NULL;
	}
#endif

	base->pool = pool;
	base->epfd = ep;
	base->event = event;
	base->nevent = size;
	base->task_queue = task_queue;

	return base;
}

void destroy_event_base(event_base_t *base) {
	mempool_t *pool = base->pool;

	if (base == NULL) {
		return;
	}

	pfree(pool, base->event);
	close(base->epfd);
	pfree(pool,base);
}

int event_add_in(event_base_t *base, event_t *ev) {
	int status;
	struct epoll_event event;
	int ep = base->epfd;
	connection_t *c = ev->data;

	event.events |= (EPOLLIN | EPOLLET);
	event.data.ptr = ev;

	status = epoll_ctl(ep, EPOLL_CTL_MOD,c->fd,&event);
	if (status < 0) {
		printf("[event_add_in] epoll ctl on e %d sd %d failed: %s\n",ep, c->fd,
			strerror(errno));
	}

	return status;
}

int event_add_out(event_base_t *base, event_t *ev) {
	int status;
	struct epoll_event event;
	int ep = base->epfd;
	connection_t *c = ev->data;

	event.events |= (EPOLLOUT | EPOLLET);
	event.data.ptr = ev;

	status = epoll_ctl(ep, EPOLL_CTL_MOD,c->fd,&event);
	if (status < 0) {
		printf("[event_add_out] epoll ctl on e %d sd %d failed: %s\n", ep, c->fd,
			strerror(errno));
	}

	return status;
}

int event_del_in(event_base_t *base, event_t *ev) {
	return 0;
}

int event_del_out(event_base_t *base, event_t *ev) {
	int status;
	struct epoll_event event;
	int ep = base->epfd;
	connection_t *c = ev->data;

	event.events &= ~(EPOLLOUT);
	event.data.ptr = ev;

	status = epoll_ctl(ep, EPOLL_CTL_MOD, c->fd, &event);
	if (status < 0) {
		printf("[event_del_out] epoll ctl on e %d sd %d failed: %s\n", ep, c->fd,
			strerror(errno));
	}

	return status;
}

int event_del(event_base_t *base, event_t *ev) {
	int status;
	struct epoll_event event;
	int ep = base->epfd;
	connection_t *c = ev->data;

	status = epoll_ctl(ep, EPOLL_CTL_DEL, c->fd, &event);
	if (status < 0) {
		printf("[event_del] epoll ctl on e %d sd %d failed: %s\n", ep, c->fd,
			strerror(errno));
	}

	return status;
}

int event_add_conn(event_base_t *base, connection_t *c) {
	int status;
	struct epoll_event event;
	int ep = base->epfd;
	event_t *ev = c->data;

	//event.events = EPOLLIN | EPOLLOUT | EPOLLET;
	event.events = EPOLLIN | EPOLLET;
	event.data.ptr = ev;

	status = epoll_ctl(ep, EPOLL_CTL_ADD,c->fd,&event);
	if (status < 0) {
		printf("[event_add_conn] epoll ctl on e %d sd %d failed: %s\n", ep, c->fd,
			strerror(errno));
	}

	return status;
}

int event_del_conn(event_base_t *base, connection_t *c) {
	int status;
	int ep = base->epfd;

	status = epoll_ctl(ep, EPOLL_CTL_DEL,c->fd,NULL);
	if (status < 0) {
		printf("[event_del_conn] epoll ctl on e %d sd %d failed: %s\n", ep, c->fd,
			strerror(errno));
	}

	return status;
}

int event_wait(event_base_t *base, int timeout) {
	int ep = base->epfd;
	struct epoll_event *event = base->event;
	int nevent = base->nevent;
	event_t *ev;
	mempool_t *pool = base->pool;

	for (;;) {
		int i, nsd;
		
		nsd = epoll_wait(ep,event,nevent,timeout);
		if (nsd > 0) {
			for (i = 0; i < nsd; i++) {
				struct epoll_event *e = &base->event[i];
				ev = e->data.ptr;
				ev->events = e->events;
				
				task_t *task = pmalloc(pool,sizeof(task_t));
				task->data = ev;
				push_task(base->task_queue,task);
			}
		}

		if (nsd == 0) {
			if (timeout == -1) {
				printf("[event_wait] epoll wait on e %d with %d events and %d timeout "
					"returned no events\n", ep, nevent, timeout);

				return -1;
			}
		}

		if (errno == EINTR) {
			continue;
		}

		printf("[event_wait] epoll wait on e %d with %d events failed: %s\n", ep, nevent,
			strerror(errno));
		return -1;
	}
}

void event_dispatch(event_base_t *base) {
	int status;
	while (1) {
		status = event_wait(base,1000);
	}
}
