#ifndef BUF_H
#define BUF_H

typedef struct buf_s buf_t;

struct buf_s
{
	char *start;
	char *end;
	char *pos;
	char *last;
	unsigned last_in_chain : 1;
};

struct chain_s;
typedef struct chain_s chain_t;

struct chain_s
{
	buf_t *buf;
	chain_t	*next;
};

int buf_realloc(buf_t *buf, int size);

#endif // !BUF_H