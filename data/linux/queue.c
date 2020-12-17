#include "datatype.h"
#include "memory.h"
#include "api.h"
#include <stdlib.h>

#define HEAD  0

void create_queue(apr_socket_queue *queue, apr_config *pconfig) {
	queue->size = pconfig->socket_number;
	queue->base = (int *) apr_memory_alloc(sizeof(int) * pconfig->socket_number);
	queue->writer = HEAD;
	queue->reader = HEAD - 1;

	apr_create_mutex(&(queue->mutex));
	apr_create_semaphore(&(queue->empty), pconfig->socket_number);
	apr_create_semaphore(&(queue->full), 0);
}


int enqueue(apr_socket_queue *queue, int socket) {
	int r;
	apr_wait_semaphore(&(queue->empty));
	apr_wait_mutex(&(queue->mutex));

	queue->base[queue->writer] = socket;
	queue->writer = (++queue->writer) % queue->size;
	r = TRUE;

	apr_signal_mutex(&(queue->mutex));
	apr_signal_semaphore(&(queue->full));

	return r;
}

int dequeue(apr_socket_queue *queue, int *socket) {
	int r;
	apr_wait_semaphore(&(queue->full));
	apr_wait_mutex(&(queue->mutex));

	queue->reader = (++queue->reader) % queue->size;
	*socket = queue->base[queue->reader];
	r = TRUE;

	apr_signal_mutex(&(queue->mutex));
	apr_signal_semaphore(&(queue->empty));

	return r;
}


void destroy_queue(apr_socket_queue *queue) {
	apr_memory_free(queue->base);
	queue->writer = HEAD;
	queue->reader = HEAD - 1;
	queue->size = 0;
}

