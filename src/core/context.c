#include <unistd.h>

#include "contex.h"

context_t *create_context(mempool_t *pool) {
	context_t *ctx = pmalloc(pool,sizeof(context_t));
	if (ctx == NULL) {
		return NULL;
	}

	ctx->pool = pool;

	pthread_mutex_init(&ctx->conn_mutex,NULL);
	ctx->free_connection_n = 0;
	ctx->free_connections = NULL;

	return ctx;
}

void destroy_context(context_t *ctx) {
	//
}

connection_t *get_connection(context_t *ctx) {
	connection_t *c;

	if (ctx == NULL) {
		return NULL;
	}

	pthread_mutex_lock(&ctx->conn_mutex);
	if (ctx->free_connection_n > 0) {
		c = ctx->free_connections;
		ctx->free_connections = c->data;
		ctx->free_connection_n--;
		pthread_mutex_unlock(&ctx->conn_mutex);
	}
	else {
		pthread_mutex_unlock(&ctx->conn_mutex);
		c = pmalloc(ctx->pool,sizeof(connection_t)); 
		c->recv_buf = pmalloc(ctx->pool, sizeof(buf_t));
		c->send_buf = pmalloc(ctx->pool, sizeof(buf_t));
	}

	return c;
}

void put_connection(context_t *ctx, connection_t *c) {
	if (ctx == NULL || c == NULL)
		return;

	pthread_mutex_lock(&ctx->conn_mutex);
	c->data = ctx->free_connections;
	ctx->free_connections = c;
	ctx->free_connection_n++;
	pthread_mutex_unlock(&ctx->conn_mutex);
}