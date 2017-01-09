#ifndef MESSAGE_H
#define MESSAGE_H

#include "sds.h"
#include "mem_pool.h"
#include "buf.h"

typedef struct message_s {
	mempool_t *pool;
	sds_t *head;
	sds_t *body;
}message_t;

message_t *create_message(mempool_t *pool);
void destroy_message(message_t *msg);
int set_head(message_t *msg,char *ptr,int head_len);
int set_body(message_t *msg,char *ptr, int body_len);
int get_msg_len(char *msg_buf);
message_t *parse_messge(mempool_t *pool, char *msg_buf, int msg_len);
int pack_message(mempool_t *pool, message_t *msg,buf_t *buf);

#endif // !REQUEST_H