#include <stdlib.h>

#include "buf.h"

int buf_realloc(buf_t *buf, int size) {
	int old_size = buf->end - buf->start;
	int pos = buf->pos - buf->start;
	int last = buf->last - buf->start;


	char *p = realloc(buf->start, size);
	if (p == NULL) {
		return -1;
	}
	buf->start = p;
	buf->end = p + size;
	buf->pos = p + pos;
	buf->last = p + last;

	//���ݲ���Ҫ����������Ч��
	if (size < old_size) {
		buf->pos = buf->start;
		buf->last = buf->start;
	}

	return 0;
}