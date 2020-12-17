//
// Created by lishujun on 2/14/19.
//
#include "datatype.h"

#ifndef IHTTPD_FOR_LINUX_HASHTABLE_H
#define IHTTPD_FOR_LINUX_HASHTABLE_H

void list_insert_front(node **pnode, element *e);

void list_destroy(node **pnode);

element *list_search(node *pnode, char *key);

apr_hash_table *create_hash_table(size_t size);

element *create_element(void *data, char *key, size_t size);

int mapping(apr_hash_table *pthis, char *key);

void chained_hash_insert(apr_hash_table *pthis, element *e);

element *chained_hash_search(apr_hash_table *pthis, char *key);

void destroy_apr_hash_table(apr_hash_table *pthis);


#endif //IHTTPD_FOR_LINUX_HASHTABLE_H
