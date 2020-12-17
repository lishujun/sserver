//
// Created by lishujun on 2/14/19.
//

#ifndef IHTTPD_FOR_LINUX_RESPONSE_H
#define IHTTPD_FOR_LINUX_RESPONSE_H

typedef struct response_info {
	int state;
	char *description;
	int length;
	char *type;
} response_info;

void replace_token(char *p, char token1, char token2);

char *uri_map_path(char *uri);

FILE *open_html_file(char *path);

int create_stream(char *s, response_info *p_info);

char *get_file_type(char *path);

char *response(request_t *p_request, long *len);


#endif //IHTTPD_FOR_LINUX_RESPONSE_H
