#include <stdio.h>

#ifndef __DATATYPE
#define __DATATYPE
#define __OS__LINUX
//the code on os platform

#ifdef __OS__WINDOWS
#include <windows.h>
#define __thread __stdcall
typedef int (__thread *pf_thread)(void *);
typedef int apr_thread_t;
typedef int apr_thread_mutex;
typedef int apr_thread_semaphore;
typedef int apr_thread_wait;
#endif


#ifdef __OS__LINUX

#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

#define __thread

typedef void *(*pf_thread)(void *);

typedef pthread_t apr_thread_t;
typedef pthread_mutex_t apr_thread_mutex;
typedef sem_t apr_thread_semaphore;
typedef pthread_cond_t apr_thread_wait;
#endif

#define TRUE  1
#define FALSE 0
typedef enum {
	RUN, STOP, SUSPENDED
} thread_state;           /* THREAD STATE*/
typedef enum {
	START, SHUTDOWN, RESTART
} apr_server_state;   /* SERVER EVENT */

/* SOCKET */
#define INVALID_SOCKET ~0

/* CONFIG */
typedef struct apr_config {
	int port;
	int thread_number;
	int socket_number;
	char *root;
	char *index_page;
} apr_config;

/* THREAD */
typedef struct apr_thread_info {
	apr_thread_t thread;
	apr_thread_mutex worked;
	apr_thread_wait allocated;
	int socket;
	thread_state state;
	apr_server_state svr_state;
} apr_thread_info;

typedef struct apr_thread_manager {
	apr_thread_info listener;
	apr_thread_info allocator;
	apr_thread_info checker;
} apr_thread_manager;

/* QUEUE */
typedef struct apr_socket_queue {
	int size;
	int *base;
	apr_thread_mutex mutex;
	apr_thread_semaphore full;
	apr_thread_semaphore empty;
	volatile int writer;
	volatile int reader;
} apr_socket_queue;

/* HASH */
typedef struct element {
	char *key;
	void *data;
	size_t size;
} element;

typedef struct node {
	element *e;
	struct node *next;
} node;

typedef struct apr_hash_table {
	node *(*base)[];
	size_t size;
} apr_hash_table;

/*HTTP REQUEST */
#define REQ_BUF_SIZ 1024 * 4
#define REQ_HASH_SIZ 30

#define METHOD   "METHOD"
#define URI      "URI"
#define PROTOCOL "PROTOCOL"

typedef struct request_t {
	apr_hash_table *header;
	apr_hash_table *form;
	apr_hash_table *query_string;
} request_t;

/* RESPONSE */
#define RESP_HEADER_SIZ 100 * 5


#endif
