
#include <assert.h>
#include <string.h>
#include "datatype.h"
#include "memory.h"
#include "hashtable.h"

void list_insert_front(node **pnode, element *e) {
	node *new_item = (node *) apr_memory_alloc(sizeof(node));
	new_item->e = e;
	new_item->next = *pnode;
	*pnode = new_item;
}

void list_destroy(node **pnode) {
	node *cur, *tmp;
	cur = tmp = &*pnode;
	while (cur) {
		cur = cur->next;
		apr_memory_free(tmp->e->data);
		apr_memory_free(tmp->e->key);
		apr_memory_free(tmp->e);
		apr_memory_free(tmp);
		tmp = cur;
	}
	pnode = NULL;
}

element *list_search(node *pnode, char *key)//UPDATE
{
	node *cur = pnode;
	while (cur) {
		if (strcmp(cur->e->key, key) == 0)//UPDATE
			return cur->e;
		cur = cur->next;
	}
	return NULL;
}


apr_hash_table *create_hash_table(size_t size) {
	int i;
	apr_hash_table *pthis = (apr_hash_table *) apr_memory_alloc(sizeof(apr_hash_table));
	pthis->base = (void *) apr_memory_alloc(sizeof(node *) * size);
	pthis->size = size;
	for (i = 0; i < pthis->size; i++) {
		(*pthis->base)[i] = NULL;
	}
	return pthis;
}

element *create_element(void *data, char *key, size_t size) {
	void *p = apr_memory_alloc(sizeof(char) * size);
	element *e = (element *) apr_memory_alloc(sizeof(element));
	memcpy(p, data, size);
	e->data = p;
	e->key = apr_memory_alloc(strlen(key) + 1);
	strcpy(e->key, key);//UPDATE
	e->size = size;
	return e;
}

int mapping(apr_hash_table *pthis, char *key) {
	unsigned int val = 0;
	while (*key != '\0')
		val = (val << 5) + *key++;

	return val % pthis->size;
	//the function is h in CLRS, map key to apr_hash_table
}

void chained_hash_insert(apr_hash_table *pthis, element *e) {
	int cur = mapping(pthis, e->key);
	list_insert_front(&((*pthis->base)[cur]), e);
}

element *chained_hash_search(apr_hash_table *pthis, char *key) {
	int cur;
	cur = mapping(pthis, key);
	return list_search((*pthis->base)[cur], key);
}

void destroy_apr_hash_table(apr_hash_table *pthis) {
	int i = 0;

	while (i < pthis->size) {
		if ((*pthis->base)[i] != NULL) {
			list_destroy((*(pthis->base))[i]);
		}
		i++;
	}
	apr_memory_free(pthis->base);
	apr_memory_free(pthis);//i'm forget it again
}
