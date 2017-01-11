#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "connection.h"
#include "contex.h"
#include "message.h"
#include "../biz/msg_handler.h"

#define BUFFER_SIZE 1024

int unix_send(connection_t *c, char *buf, int size) {
	int n;
	int err;

	for (;;) {
		n = send(c->fd,buf,size,0);
		if (n > 0) {
			return n;
		}

		err = errno;

		if (n == 0) {
			printf("send() returned zero\n");
			return n;
		}
		if (err == EAGAIN || err == EINTR) {
			printf("send() not ready!\n");

			if (err == EAGAIN) {
				return EAGAIN;
			}
		}
		else {
			return -1;
		}
	}
}

int unix_recv(connection_t *c, char *buf, int size) {
	int n;
	int err;

	do {
		n = recv(c->fd,buf,size,0);
		if (n == 0) {
			return 0;
		}
		if (n > 0) {
			return n;
		}

		err = errno;
		if (err == EAGAIN || err == EINTR) {
			n = EAGAIN;
		}
		else {
			break;
		}

	} while (err == EINTR);

	return n;
}

#if 0
void set_socket_reuse(int sock) {
	int yes = 1;

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
}
#endif

int set_noblocking(int fd) {
	int op;

	op = fcntl(fd,F_GETFL,0);
	fcntl(fd,F_SETFL,op | O_NONBLOCK);

	return op;
}

int init_socket(int port) {
	signal(SIGPIPE,SIG_IGN);
	signal(SIGCHLD, SIG_IGN);

	int listenfd = socket(AF_INET,SOCK_STREAM,0);
	set_socket_option(listenfd);

	struct sockaddr_in address;

	memset(&address, 0, sizeof(address));
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(port);
	bind(listenfd, (struct sockaddr*)&address, sizeof(address));
	listen(listenfd, 1024);
	set_noblocking(listenfd);

	return listenfd;
}

void on_accept(event_t *ev) {
	connection_t *c = ev->data;
	int listenfd = c->fd;
	mempool_t *pool = ctx->pool;

	printf("on accept!\n");

	while (1) {
		int fd = accept(listenfd,NULL,NULL);
		if (fd > 0) {
			set_noblocking(fd);
			event_t *e = pmalloc(pool,sizeof(event_t));
			connection_t *c = get_connection((context_t *)ctx);
			c->fd = fd;
			c->recv = unix_recv;
			c->send = unix_send;

			assert(c->recv_buf != NULL);
			c->recv_buf->start = malloc(BUFFER_SIZE);
			c->recv_buf->end = c->recv_buf->start + BUFFER_SIZE;
			c->recv_buf->pos = c->recv_buf->start;
			c->recv_buf->last = c->recv_buf->pos;

			c->send_buf->start = malloc(BUFFER_SIZE);
			c->send_buf->end = c->send_buf->start + BUFFER_SIZE;
			//c->send_buf->pos = c->send_buf->start;
			//c->send_buf->last = c->send_buf->pos;

			e->data = c;
			e->fd = fd;
			e->handler = on_handler;

			c->data = e;
			event_add_conn(ctx->base,c,1);
		}
		else {
			if (errno == EAGAIN) {
				break;
			}
		}
	}
}

void on_handler(event_t *ev) {
	int events = ev->events;
	connection_t *c = ev->data;
	mempool_t *pool = ctx->pool;
	int iRet;
	int received;

	if (c->fd < 0) {
		return;
	}
	
	if (events & EPOLLIN) {
		int n;
		int last;
		int size;

		for (;;) {
			size = c->recv_buf->end - c->recv_buf->last;
			if (size == 0) {
				int new_size = (c->recv_buf->end - c->recv_buf->start) << 2;
				iRet = buf_realloc(c->recv_buf, new_size);
				if (iRet < 0) {
					return;
				}
				size = new_size;
			}

			n = c->recv(c, c->recv_buf->last, size);
			if (n == EAGAIN) {
				event_add_in(ctx->base,ev);
				break;
			}
			if (n == 0) {
				//对方关闭连接
				event_del(ctx->base, ev);
				close_connection(c);
				put_connection((context_t *)ctx,c);
				
				pfree(pool,ev);
				ev = NULL;

				return;
			}
			if (n < 0) {
				//出错
				event_del(ctx->base, ev);
				close_connection(c);
				put_connection((context_t *)ctx, c);

				pfree(pool,ev);
				
				return;
			}
			if (n > 0) {
				c->recv_buf->last += n;
			}

			//循环处理接受的包
			received = c->recv_buf->last - c->recv_buf->pos;
			while (received > 0) {
				int msg_len = get_msg_len(c->recv_buf->pos);
				if (msg_len + 4 <= received) {
					//收到的是完整的包
					received -= msg_len + 4;
					c->recv_buf->pos += 4;

					if (process_biz(pool, c->recv_buf->pos, msg_len, c->send_buf)) {
						free(c->recv_buf->start);
						put_connection((context_t *)ctx, c);
						
						return;
					}

					//发送给客户端
					send_buf(c);

					c->recv_buf->pos += msg_len;
					if (c->recv_buf->pos == c->recv_buf->last) {
						c->recv_buf->pos = c->recv_buf->start;
						c->recv_buf->last = c->recv_buf->start;
					}
				}
				else {
					//包不完整，需要等待下次接收
					//received = c->recv_buf->last - c->recv_buf->pos;
					if (c->recv_buf->pos > c->recv_buf->start) {
						memmove(c->recv_buf->start, c->recv_buf->pos, received);
						c->recv_buf->last = c->recv_buf->start + received;
						c->recv_buf->pos = c->recv_buf->start;
					}

					break;
				}
				
				//
			}//while

		}//for
		
	}//if
	else if (events & EPOLLOUT) {
		//继续发完剩下的
		send_buf(c);
	}
	else {
		//出错处理
	}
}

int send_buf(connection_t *c) {
	buf_t *send_buf = c->send_buf;
	int size = send_buf->last - send_buf->pos;
	event_t *ev = c->data;
	int n;
	
	for (;;) {
		n = c->send(c, send_buf->pos, size);
		if (n == EAGAIN || n == 0) {
			break;
		}

		size -= n;
		send_buf->pos += n;
		if (size == 0) {
			//数据发完了
			send_buf->pos = send_buf->start;
			send_buf->last = send_buf->start;
			break;
		}
	}

	if (size > 0) {
		event_add_out(ctx->base, ev);
	}

	return 0;
}

void close_connection(connection_t *c) {
	close(c->fd);
	c->fd = -1;

	if (c->recv_buf->start) {
		free(c->recv_buf->start);
		c->recv_buf->start = NULL;
	}	
}