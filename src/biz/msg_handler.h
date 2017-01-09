#ifndef MSGE_HANDLER_H
#define MSGE_HANDLER_H

#include "../core/message.h"

typedef int(*msg_handler_pt)(message_t *, message_t *);

typedef struct msg_handler_s {
	const char *msg_type;
	msg_handler_pt msg_handler;
}msg_handler_t;

int process_biz(mempool_t *pool, char *msg_buf, int msg_len, buf_t *send_buf);

int handler1(message_t *req, message_t *resp);

#endif // !MSGE_HANDLER_H