#include <stdio.h>
#include <string.h>

#include "json-c/json.h"

#include "msg_handler.h"

msg_handler_t biz_handlers[] = {
	{
		"test1",
		handler1
	},
	{
		"",
		NULL
	}
};

int process_biz(mempool_t *pool, char *msg_buf, int msg_len,buf_t *send_buf) {
	message_t *msg = parse_messge(pool, msg_buf, msg_len);
	if (msg == NULL) {
		return -1;
	}

	json_object *head_obj = json_tokener_parse(msg->head->buf);
	if (is_error(head_obj)) {
		destroy_message(msg);
		return -1;
	}

	json_object *msg_type_obj;
	json_bool result = json_object_object_get_ex(head_obj, "msgtype", &msg_type_obj);
	if (!result) {
		json_object_put(head_obj);
		destroy_message(msg);
		return -1;
	}

	const char *msgtype = json_object_get_string(msg_type_obj);
	if (msgtype == NULL) {
		json_object_put(head_obj);
		destroy_message(msg);
		return -1;
	}

	printf("[msgtype]:%s\n",msgtype);

	message_t *resp = create_message(pool);

	int i;
	for (i = 0;; i++) {
		if (biz_handlers[i].msg_handler == NULL) {
			break;
		}

		if (strcmp(msgtype, biz_handlers[i].msg_type) == 0) {
			biz_handlers[i].msg_handler(msg, resp);
			break;
		}
	}

	//打包消息
	if (pack_message(pool, resp, send_buf)) {
		json_object_put(head_obj);
		destroy_message(msg);
		destroy_message(resp);
		return -1;
	}

	//发送响应给客户端

	json_object_put(head_obj);
	destroy_message(msg);
	destroy_message(resp);

	return 0;
}

int handler1(message_t *req, message_t *resp) {
	printf("[msg] %s\n", req->body->buf);
	if (resp) {
		set_head(resp,req->head->buf,req->head->len);
		set_body(resp, req->body->buf, req->body->len);
	}

	return 0;
}