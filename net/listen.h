//
// Created by lishujun on 2/14/19.
//

#ifndef IHTTPD_FOR_LINUX_LISTEN_H
#define IHTTPD_FOR_LINUX_LISTEN_H

int network_initialize();

int apr_socket_accept();

int apr_socket_recv(int fd, char *buf, int len);

int apr_socket_send(int fd, char *buf, int len);

void apr_socket_close(int fd);

#endif //IHTTPD_FOR_LINUX_LISTEN_H
