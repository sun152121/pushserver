#ifndef RBTREE_H
#define RBTREE_H

#include <stdio.h>
#include <stdint.h>

#define rbtree_red(_node)           ((_node)->color = 1)
#define rbtree_black(_node)         ((_node)->color = 0)
#define rbtree_is_red(_node)        ((_node)->color)
#define rbtree_is_black(_node)      (!rbtree_is_red(_node))
#define rbtree_copy_color(_n1, _n2) ((_n1)->color = (_n2)->color)

typedef struct rbnode_s rbnode_t;
typedef struct rbtree_s rbtree_t;

struct rbnode_s {
    rbnode_t* left;     /* left link */
	rbnode_t* right;    /* right link */
	rbnode_t* parent;   /* parent link */
	int64_t  key;       /* key for ordering */
    void*     data;     /* opaque data */
    uint8_t  color;     /* red | black */
};

struct rbtree_s {
	rbnode_t *root;     /* root node */
	rbnode_t *sentinel; /* nil node */
};

void rbtree_node_init(rbnode_t *node);
void rbtree_init(rbtree_t *tree, rbnode_t *node);
rbnode_t *rbtree_min(rbtree_t *tree);
void rbtree_insert(rbtree_t *tree, rbnode_t *node);
void rbtree_delete(rbtree_t *tree, rbnode_t *node);

#endif
