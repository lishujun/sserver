#include "datatype.h"
#include <windows.h>
#include <stdlib.h>

#define HEAD  0
#define TRUE  1
#define FALSE 0


void create_queue(apr_socket_queue *queue,apr_config *pconfig)
{
	queue->size = pconfig->socket_number;
	queue->base = (int*)apr_memory_alloc(sizeof(int)*pconfig->socket_number);
	queue->writer  = HEAD;
	queue->reader  = HEAD - 1;
	queue->mutex   = apr_create_mutex(1,1);
	queue->empty   = apr_create_mutex(pconfig->socket_number,pconfig->socket_number);
	queue->full    = apr_create_mutex(0,pconfig->socket_number);
}


int enqueue(apr_socket_queue *queue,int socket)
{
	int r;
	apr_wait_mutex(queue->empty,INFINITE);
	apr_wait_mutex(queue->mutex,INFINITE);

	//临界区
	queue->base[queue->writer] = socket;
	queue->writer = (++queue->writer) % queue->size;
	r = TRUE;

	apr_signal_mutex(queue->mutex);
	apr_signal_mutex(queue->full);

	return r;
}

int dequeue(apr_socket_queue *queue,int *socket)
{
	int r;
	apr_wait_mutex(queue->full,INFINITE);
	apr_wait_mutex(queue->mutex,INFINITE);

	//临界区
	queue->reader = (++queue->reader) % queue->size;
	*socket = queue->base[queue->reader];
	r = TRUE;

	apr_signal_mutex(queue->mutex);
	apr_signal_mutex(queue->empty);

	return r;
}


void destroy_queue(apr_socket_queue *queue)
{
	apr_memory_free(queue->base);
	queue->writer = HEAD;
	queue->reader = HEAD -1;
	queue->size = 0;
}

