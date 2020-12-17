//
// Created by lishujun on 2/14/19.
//
#include "datatype.h"

#ifndef IHTTPD_FOR_LINUX_MEMORY_H
#define IHTTPD_FOR_LINUX_MEMORY_H

void apr_memory_initialize();

int apr_wait_semaphore(apr_thread_semaphore *p_semaphore);

void apr_destroy_memory();

void *apr_memory_alloc(size_t size);

void apr_memory_free(void *p);

#endif //IHTTPD_FOR_LINUX_MEMORY_H
