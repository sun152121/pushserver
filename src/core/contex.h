#ifndef CONTEXT_H
#define CONTEXT_H

#include <pthread.h>

#include "mem_pool.h"
#include "connection.h"

typedef struct context_s
{
	mempool_t *pool;
	event_base_t *base;
	connection_t *free_connections;
	int free_connection_n;
	pthread_mutex_t conn_mutex;
}context_t;

#define add_conn(ctx,c)								\
	do {											\
		pthread_mutex_lock(&ctx->conn_mutex);		\
		c->data = ctx->free_connections;			\
		ctx->free_connections = c;					\
		ctx->free_connection_n++;					\
		pthread_mutex_unlock(&ctx->conn_mutex);		\
	}while(0)

context_t *create_context(mempool_t *pool);
void destroy_context(context_t *ctx);
connection_t *get_connection(context_t *ctx);
void put_connection(context_t *ctx,connection_t *c);

context_t *ctx;

#endif // !CONTEXT_H