//
// Created by lishujun on 2/14/19.
//

#include "datatype.h"

#ifndef IHTTPD_FOR_LINUX_QUEUE_H
#define IHTTPD_FOR_LINUX_QUEUE_H

void create_queue(apr_socket_queue *queue, apr_config *pconfig);

int enqueue(apr_socket_queue *queue, int socket);

int dequeue(apr_socket_queue *queue, int *socket);

void destroy_queue(apr_socket_queue *queue);

#endif //IHTTPD_FOR_LINUX_QUEUE_H
