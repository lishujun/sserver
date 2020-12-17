#include <memory.h>
#include <stdlib.h>
#include "datatype.h"
#include "api.h"

apr_thread_mutex lock;

void apr_memory_initialize() {
	apr_create_mutex(&lock);
}

void apr_destroy_memory() {
	apr_destroy_mutex(&lock);
}

void *apr_memory_alloc(size_t size) {
	void *p;
	apr_wait_mutex(&lock);
	p = malloc(size);
	apr_signal_mutex(&lock);
	return p;
}

void apr_memory_free(void *p) {
	apr_wait_mutex(&lock);
	free(p);
	apr_signal_mutex(&lock);
}
