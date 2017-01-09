#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "mem_pool.h"
#include "hash.h"

typedef unsigned int (*hash_fun_pt)(const void	*key, int len);
typedef int(*cmp_fun_pt)(const void *src,int src_len, const void *dest,int dest_len);

typedef struct hashmap_s hashmap_t;

static unsigned long hash_size[] = {
	53ul,         97ul,         193ul,       389ul,       769ul,
	1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
	49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
	1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
	50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
	1610612741ul, 3221225473ul, 4294967291ul
};

struct node_s;
typedef struct node_s node_t;

struct node_s {
	int key_hash;
	const void *key;
	int len;
	void *val;
	node_t *next;
};

typedef struct entry_s {
	int hash;
	node_t *next;
} entry_t;

typedef struct hashmap_s {
	mempool_t	*pool;
	int size_index;
	int max_size_index;
	int bucket_size;	//桶大小
	double factor;		//负载因子
	int	elements;		//当前元素个数
	int max_elements;	//最大元素个数，超过此值hashmap会自动扩容
	entry_t *bucket;
	unsigned int (*hash_fun)(const void *key,int len);
	int (*cmp_fun)(const void *src, int src_len, const void *dest, int dest_len);
} hashmap_t;

hashmap_t *create_hashmap(mempool_t *pool,double factor,hash_fun_pt hash,cmp_fun_pt cmp);
int hashmap_insert(hashmap_t *hm,const void *key, int len,void *val);
void *hashmap_find(hashmap_t *hm, const void *key, int len);
void hashmap_delete(hashmap_t *hm, const void *key, int len);
void destroy_hashmap(hashmap_t *hm);

int str_cmp(const void *src, int src_len, const void *dest, int dest_len);
int int_cmp(const void *src, int src_len, const void *dest, int dest_len);

#endif // ! HASHMAP_H