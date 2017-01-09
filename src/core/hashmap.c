#include "hashmap.h"
#include "string.h"

int __hashmap_insert(hashmap_t *hm, const void *key, int len, void *val);
void __hashmap_expend(hashmap_t *hm);

hashmap_t *create_hashmap(mempool_t *pool,double factor, hash_fun_pt hash, cmp_fun_pt cmp) {
	/*mempool_t *pool = init_mempool(POOL_BLOCK_DEFAULT_TOTAL_SIZE,0);
	if (pool == NULL) {
		return NULL;
	}*/

	hashmap_t *hm = pmalloc(pool,sizeof(hashmap_t));
	if (hm == NULL) {
		return NULL;
	}

	hm->pool = pool;
	hm->hash_fun = hash;
	hm->cmp_fun = cmp;
	hm->factor = factor;
	hm->size_index = 0;
	hm->max_size_index = sizeof(hash_size) / (sizeof(hash_size[0]));
	hm->bucket_size = hash_size[0];
	hm->elements = 0;
	hm->max_elements = hm->bucket_size * factor;
	hm->bucket = pmalloc(pool,hm->bucket_size * sizeof(entry_t));
	memset(hm->bucket,0, hm->bucket_size * sizeof(entry_t));
	if (hm->bucket == NULL) {
		return NULL;
	}

	return hm;
}

int hashmap_insert(hashmap_t *hm, const void *key, int len, void *val) {
	int iRet = __hashmap_insert(hm,key,len,val);
	if (hm->elements > hm->max_elements && hm->size_index < hm->max_size_index) {
		__hashmap_expend(hm);
	}

	return iRet;
}

void __hashmap_expend(hashmap_t *hm) {
	int bucket_size = hm->bucket_size;
	entry_t *bucket = hm->bucket;
	int i;
	int hash;
	node_t *node;

	hm->bucket_size = hash_size[++hm->size_index];
	hm->max_elements = hm->factor * hm->bucket_size;

	hm->bucket = pmalloc(hm->pool,hm->bucket_size * sizeof(entry_t));

	for (i = 0; i < bucket_size; i++) {
		node_t *n = bucket[i].next;
		while (n->next) {
			node = n->next;
			hash = n->key_hash % hm->bucket_size;
			entry_t *e = &hm->bucket[hash];
			n->next = e->next;
			e->next = n;
			n = node;
		}
	}

	pfree(hm->pool,bucket);
}

int __hashmap_insert(hashmap_t *hm, const void *key,int len, void *val) {
	unsigned int key_hash = hm->hash_fun(key, len);
	unsigned int hash = key_hash % hm->bucket_size;
	mempool_t *pool = hm->pool;
	node_t *node = pmalloc(pool, sizeof(node_t));
	if (node == NULL) {
		return -1;
	}
	node->key_hash = key_hash;
	node->key = key;
	node->len = len;
	node->val = val;
	node->next = NULL;

	entry_t *e = &hm->bucket[hash];
	if (e->next == NULL) {
		e->next = node;
		e->hash = hash;

		hm->elements++;
	}
	else {
		node_t *n = e->next;
		if (hm->cmp_fun(n->key, n->len, node->key, node->len) == 0) {
			n->val = val;
			return 0;
		}
		else {
			while (n->next) {
				n = n->next;
				if (hm->cmp_fun(n->key, n->len, node->key, node->len) == 0) {
					n->val = val;
					return 0;
				}
			}

			n->next = node;
			hm->elements++;
		}
	}

	return 0;
}

void *hashmap_find(hashmap_t *hm, const void *key,int len) {
	unsigned int key_hash = hm->hash_fun(key, len);
	unsigned int hash = key_hash % hm->bucket_size;

	entry_t *e = &hm->bucket[hash];
	if (e->next == NULL) {
		return NULL;
	}

	node_t *n = e->next;
	while (n) {
		if (hm->cmp_fun(n->key, n->len, key, len) == 0) {
			return n->val;
		}
		n = n->next;
	}

	return NULL;
}

void hashmap_delete(hashmap_t *hm, const void *key,int len) {
	unsigned int key_hash = hm->hash_fun(key, len);
	unsigned int hash = key_hash % hm->bucket_size;

	entry_t *e = &hm->bucket[hash];
	if (e->next == NULL) {
		return;
	}

	node_t *next;
	node_t *prev = e->next;
	node_t *n = prev->next;

	if (hm->cmp_fun(prev->key, prev->len, key, len) == 0) {
		prev->next = NULL;
		e->next = n;

		pfree(hm->pool,prev);

		return;
	}
	while (n) {
		next = n->next;
		if (hm->cmp_fun(n->key, n->len, key, len) == 0) {
			prev->next = next;
			n->next = NULL;

			pfree(hm->pool, n);

			return;
		}

		if (next == NULL) {
			return;
		}

		prev = n;
		n = next;
		next = next->next;

	}
}

void destroy_hashmap(hashmap_t *hm) {
	mempool_t *pool = hm->pool;
	int i;
	for (i = 0; i < hm->bucket_size; i++) {
		entry_t *e = &hm->bucket[i];
		if (e->next) {
			node_t *n = e->next;
			while (n) {
				node_t *node = n->next;
				pfree(hm->pool,n);
				n = node;
			}
		}
	}

	pfree(pool,hm);
}

int str_cmp(const void *src, int src_len, const void *dest, int dest_len) {
	char *pSrc = (char *)src;
	char *pDest = (char *)dest;
	int i;

	if (src_len != dest_len) {
		return -1;
	}
	
	for (i = 0; i < src_len; i++) {
		if (pSrc[i] != pDest[i]) {
			return -1;
		}
	}

	return 0;
}

int int_cmp(const void *src, int src_len, const void *dest, int dest_len) {
	int *pSrc = (int *)src;
	int *pDest = (int *)dest;
	
	return *pSrc == *pDest;
}