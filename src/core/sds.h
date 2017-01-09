#ifndef SDS_H
#define SDS_H

#define SDS_MAX_PREALLOC (1024*1024)

#include <sys/types.h>
#include <stdarg.h>

typedef struct sds_s
{
	unsigned int len;
	unsigned int free;
	char buf[];
}sds_t;

static inline size_t sdslen(const char *s) {
	sds_t *sds = (void *)(s - sizeof(sds_t));
	return sds->len;
}

static inline size_t sdsavail(const char *s) {
	sds_t *sds = (void *)(s - sizeof(sds_t));
	return sds->free;
}

#endif // !SDS_H