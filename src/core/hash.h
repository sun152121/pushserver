#ifndef HASH_H
#define HASH_H

unsigned int murmur_hash(const void	*key, int len);
unsigned int int_hash(const void *key, int len);

#endif