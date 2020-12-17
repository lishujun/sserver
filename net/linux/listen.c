#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "datatype.h"
#include "global.h"
#include "listen.h"

int server_sockfd;
int server_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;

int network_initialize() {
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sockfd == -1) {
		printf("socket failed\n");
		return FALSE;
	}

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = htons(gs_config.port);
	server_len = sizeof(server_address);
	if (bind(server_sockfd, (struct sockaddr *) &server_address, server_len) < 0) {
		printf("bind failed\n");
		return FALSE;
	}
	if (listen(server_sockfd, 5)) {
		printf("listen failed\n");
		return FALSE;
	}

	printf("network_initialize... \n");
	return TRUE;
}


int apr_socket_accept() {
	int fd;
	int client_len;

	client_len = sizeof(client_address);
	fd = accept(server_sockfd,
				(struct sockaddr *) &client_address, &client_len);
	return fd;
}


int apr_socket_recv(int fd, char *buf, int len) {
	return read(fd, buf, len);
}

int apr_socket_send(int fd, char *buf, int len) {
	return write(fd, buf, len);//strlen(buf)+1,10
}

void apr_socket_close(int fd) {
	close(fd);
}

