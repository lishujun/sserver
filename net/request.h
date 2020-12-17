//
// Created by lishujun on 2/14/19.
//

#include "hashtable.h"

#ifndef IHTTPD_FOR_LINUX_REQUEST_H
#define IHTTPD_FOR_LINUX_REQUEST_H

char *get_line(char **s);

char *get_line_part(char **s, char token);

int read_request_line(apr_hash_table *htable, char *s1);

int read_request_header(apr_hash_table *htable, char *s1);

void create_request_structure(request_t **p_request);

void destroy_request_structure(request_t **p_request);

void read_request(request_t *p_request, char *buffer, int len);

#endif //IHTTPD_FOR_LINUX_REQUEST_H
