#include <string.h>
#include <arpa/inet.h>

#include "message.h"
#include "buf.h"

message_t *create_message(mempool_t *pool) {
	message_t *msg = pmalloc(pool,sizeof(message_t));
	if (msg == NULL) {
		return NULL;
	}
	msg->pool = pool;
	msg->head = NULL;
	msg->body = NULL;

	return msg;
}

void destroy_message(message_t *msg) {
	if (msg == NULL) {
		return;
	}

	mempool_t *pool = msg->pool;
	sds_t *head = msg->head;
	sds_t *body = msg->body;

	if (head) {
		pfree(pool, head);
	}
	if (body) {
		pfree(pool, body);
	}
}

int set_head(message_t *msg,char *ptr, int head_len) {
	mempool_t *pool = msg->pool;
	msg->head = NULL;

	sds_t *head;

	head = pmalloc(pool,2 * head_len + sizeof(sds_t));
	if (head == NULL) {
		return -1;
	}

	head->len = head_len;
	head->free = head_len;

	if (head_len > 0) {
		memcpy(head->buf, ptr, head_len);
		head->buf[head_len] = '\0';
	}

	msg->head = head;

	return 0;
}

int set_body(message_t *msg,char *ptr, int body_len) {
	mempool_t *pool = msg->pool;
	msg->body = NULL;

	sds_t *body;

	body = pmalloc(pool,2 * body_len + sizeof(sds_t));
	if (body == NULL) {
		return -1;
	}

	body->len = body_len;
	body->free = body_len;

	if (body_len > 0) {
		memcpy(body->buf, ptr, body_len);
		body->buf[body_len] = '\0';
	}

	msg->body = body;

	return 0;
}

int get_msg_len(char *msg_buf) {
	int len = *((int*)msg_buf);

	return ntohl(len);
}

message_t *parse_messge(mempool_t *pool,char *msg_buf,int msg_len) {
	message_t *msg = create_message(pool);
	if (msg == NULL) {
		return NULL;
	}

	int i;
	char *p = msg_buf;
	for (i = 0; i < msg_len; i++) {
		if (*(p + i) == '\r' && *(p + i + 1) == '\n') {
			//msg head结束
			set_head(msg,p,i);

			i += 2;
			p = msg_buf + i;
			set_body(msg,p,msg_len - i);

			return msg;
		}
	}

	//只有head没有body,可以没有\r\n
	set_head(msg,p,msg_len);
	set_body(msg,NULL,0);

	return msg;
}

int pack_message(mempool_t *pool, message_t *msg,buf_t *buf) {
	if (msg == NULL || buf == NULL) {
		return -1;
	}

	//4个字节长度 包头长度 分隔符（\r\n）长度 包体长度
	int msg_len = 0;
	int total;
	if (msg->head) {
		msg_len += msg->head->len;
	}
	if (msg->body) {
		msg_len += msg->body->len;
	}
	msg_len += 2;
	total = msg_len + 4;

	int buf_size = buf->end - buf->start;
	if (buf_size < total) {
		if (buf_realloc(buf, total)) {
			return -1;
		}
	}

	buf->pos = buf->start;
	buf->last = buf->start;

	*(int *)(buf->last) = htonl(msg_len);
	buf->last += 4;

	memcpy(buf->last,msg->head->buf,msg->head->len);
	buf->last += msg->head->len;

	memcpy(buf->last, "\r\n", 2);
	buf->last += 2;

	memcpy(buf->last, msg->body->buf, msg->body->len);
	buf->last += msg->body->len;

	return 0;
}