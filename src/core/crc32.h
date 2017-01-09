#ifndef CRC32_H
#define CRC32_H

#include <stdint.h>
#include <stddef.h>

extern uint32_t crc32_table16[];
extern uint32_t crc32_table256[];

static inline uint32_t crc32_short(char	*p, size_t len) {
	char c;
	int crc;

	crc = 0xffffffff;

	while (len--)
	{
		c = *p++;
		crc = crc32_table16[(crc ^ (c & 0xf)) & 0xf] ^ (crc >> 4);
		crc = crc32_table16[(crc ^ (c >> 4)) & 0xf] ^ (crc >> 4);
	}

	return crc ^ 0xffffffff;
}

static inline uint32_t crc32_long(char *p, size_t len) {
	uint32_t crc;
	
	crc = 0xffffffff;

	while (len--)
	{
		crc = crc32_table256[(crc ^ *p++) & 0xff] ^ (crc >> 8);
	}

	return crc ^ 0xffffffff;
}

#endif
