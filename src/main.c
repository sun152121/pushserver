#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "core/mem_pool.h"
#include "core/rbtree.h"
#include "core/hashmap.h"
#include "core/crc32.h"
#include "core/task_queue.h"
#include "core/connection.h"
#include "core/contex.h"
#include "core/event.h"
#include "core/threadpool.h"

void test1();
void test2();
void test3();
void test4();
void test5(int argc, char *argv[]);
void test6();
void test7();
void daemonize(void);

int main(int argc,char *argv[])
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5(argc,argv);
	//test6();
	test7();
    return 0;
}

void test1()
{
	mempool_t* pool = create_mempool(POOL_BLOCK_DEFAULT_TOTAL_SIZE,1);

	char* p = pmalloc(pool,5);
	//memcpy(p,"test1",sizeof("test1"));

	printf("p[%s]\n",p);

	pfree(pool,p);

	p = pmalloc(pool,5);
	printf("p[%s]\n", p);

	pfree(pool,p);

	destry_mempool(pool);
}

void test2() 
{
	while (1) {
		test1();
		//usleep(100);
		sleep(1);
	}
}

void test3() {
	rbtree_t tree;
	rbnode_t sentinel;
	rbnode_t* node;
	int i;

	rbtree_init(&tree,&sentinel);

	node = malloc(sizeof(rbnode_t));
	node->key = 1;
	node->data = "test1";
	rbtree_insert(&tree,node);

	node = malloc(sizeof(rbnode_t));
	node->key = 4;
	node->data = "test3";
	rbtree_insert(&tree, node);

	node = malloc(sizeof(rbnode_t));
	node->key = 2;
	node->data = "test5";
	rbtree_insert(&tree, node);

	node = malloc(sizeof(rbnode_t));
	node->key = crc32_short("test6",sizeof("test6"));
	node->data = "test6";
	rbtree_insert(&tree,node);


}

void test4() {
	mempool_t* pool = create_mempool(POOL_BLOCK_DEFAULT_TOTAL_SIZE, 0);
	if (pool == NULL) {
		return;
	}

	hashmap_t *hm = create_hashmap(pool, 0.6, murmur_hash, str_cmp);
	if (hm == NULL) {
		return;
	}

	char key1[] = "test1";
	char val1[] = "value1";

	char key2[] = "test2";
	char val2[] = "value2";

	char key3[] = "test3";
	char val3[] = "value3";

	int iRet;

	iRet = hashmap_insert(hm,key1,sizeof(key1),val1);
	if (iRet) {
		printf("hashmap insert fail!\n");
		return;
	}

	iRet = hashmap_insert(hm,key2,sizeof(key2),val2);
	if (iRet) {
		printf("hashmap insert fail 2 !\n");
		return;
	}

	iRet = hashmap_insert(hm,key3,sizeof(key3),val3);
	if (iRet) {
		printf("hashmap insert fail 3!\n");
		return;
	}

	char *p = hashmap_find(hm,key2,sizeof(key2));
	if (p == NULL) {
		printf("hashmap find fail!\n");
		return;
	}

	p = hashmap_find(hm,key3,sizeof(key3));
	if (p == NULL) {
		printf("hashmap find fail 2 !\n");
		return;
	}

	hashmap_delete(hm,key3,sizeof(key3));

	p = hashmap_find(hm,key3,sizeof(key3));
	if (p == NULL) {
		printf("hashmap delete success!\n");
		return;
	}
	else {
		printf("hashmap delete fail!!!!!!\n");
	}
}

void test5(int argc, char *argv[])
{
	char ch;


	while ((ch = getopt(argc,argv,"c:")) > 0) {
		switch (ch)
		{
		case 'c':
			printf("%s\n", optarg);
			break;
		}
	}
}

void test6() {
	mempool_t* pool = create_mempool(POOL_BLOCK_DEFAULT_TOTAL_SIZE, 0);
	if (pool == NULL) {
		return;
	}
	task_queue_t *task_queue = create_task_queue(pool);

	task_t *task;
	task = pmalloc(pool,sizeof(task_t));
	task->data = "test1";
	push_task(task_queue,task);

	task = pmalloc(pool,sizeof(task_t));
	task->data = "test2";
	push_task(task_queue,task);

	task = pmalloc(pool, sizeof(task_t));
	task->data = "test3";
	push_task(task_queue, task);

	task = pop_task(task_queue);
	printf("[%s]\n",(char *)task->data);

	task = pop_task(task_queue);
	printf("[%s]\n", (char *)task->data);

	task = pop_task(task_queue);
	printf("[%s]\n", (char *)task->data);

}

void test7()
{
	daemonize();

	mempool_t* pool = create_mempool(POOL_BLOCK_DEFAULT_TOTAL_SIZE, 0);
	if (pool == NULL) {
		printf("create_mempool fail!\n");
		return;
	}

	ctx = create_context(pool);
	if (ctx == NULL) {
		printf("create_context fail!\n");
		return;
	}

	task_queue_t *task_queue = create_task_queue(pool);

	threadpool_t *threadpool = create_threadpool(pool,16,thread_fun,task_queue);
	threadpool->start(threadpool);

	event_base_t *base = create_event_base(pool,1024,task_queue);
	base->pool = pool;
	base->task_queue = task_queue;

	ctx->base = base;

	int port = 8083;
	int fd = init_socket(port);

	connection_t *c = get_connection((context_t *)ctx);
	c->fd = fd;
	c->recv = unix_recv;
	c->send = unix_send;

	event_t *ev = pmalloc(pool,sizeof(event_t));

	ev->data = c;
	ev->handler = on_accept;
	ev->fd = c->fd;

	c->data = ev;

	event_add_conn(base,c,0);

	event_dispatch(base);

	destroy_event_base(base);
}

#if 0
void daemon() {
	pid_t pid;

	pid = fork();
	if (pid < 0) {
		exit(1);
	}
	else if (pid > 0) {
		exit(0);
	}

	setsid();
	//chdir("/");
	umask(0);
}
#endif

void daemonize(void) {
	int fd;

	if (fork() != 0) exit(0); /* parent exits */
	setsid(); /* create a new session */

			  /* Every output goes to /dev/null. If Redis is daemonized but
			  * the 'logfile' is set to 'stdout' in the configuration file
			  * it will not log at all. */
	if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {
		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
		if (fd > STDERR_FILENO) close(fd);
	}
}