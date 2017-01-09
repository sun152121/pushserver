#ifndef CONNECTION_H
#define CONNECTION_H

#include <netinet/tcp.h>

#include "event.h"
#include "buf.h"

struct connection_s;

typedef struct connection_s connection_t;

typedef int(*recv_pt)(connection_t *c, char *buf, int size);
typedef int(*send_pt)(connection_t *c, char *buf, int size);

struct connection_s
{
	int fd;
	void *data;
	recv_pt recv;
	send_pt send;
	event_t *read;
	event_t *write;
	buf_t *recv_buf;
	buf_t *send_buf;
};

int unix_send(connection_t *c,char *buf,int size);
int unix_recv(connection_t *c,char *buf,int size);

#if 0
void set_socket_reuse(int sock);
#endif

#define set_socket_option(sock)													\
	do {																		\
		int on = 1;																\
		setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));			\
		setsockopt( sock, IPPROTO_TCP, TCP_NODELAY, (void *)&on, sizeof(on));	\
	}while(0)

int set_noblocking(int fd);

int init_socket(int port);

void on_accept(event_t *ev);
void on_handler(event_t *ev);

int event_add_conn(event_base_t *base, connection_t *c);
int event_del_conn(event_base_t *base, connection_t *c);

int send_buf(connection_t *c);

#endif // !CONNECTION_H