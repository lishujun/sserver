#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "global.h"
#include "memory.h"
#include "hashtable.h"
#include "api.h"
#include "response.h"

#define POSTFIX 7
char *postfix[POSTFIX] = {".htm", ".html", ".txt", ".jpg", ".gif", ".png", ".bmp"};
char *html_t[POSTFIX] = {"text/html", "text/html", "image/html", "image/jpeg", "image/gif", "image/png", "image/bmp"};

void replace_token(char *p, char token1, char token2) {
	while (*p != '\0') {
		if (*p == token1) {
			*p = token2;
		}
		p++;
	}
}

char *uri_map_path(char *uri) {
	int len;
	char *p;

	len = strlen(uri);

	if (uri[len - 1] == '\\') /*require defalut document*/
	{
		len = strlen(gs_config.root) + strlen(gs_config.index_page) + 2;
		p = apr_memory_alloc(len);
		strncpy(p, gs_config.root, len);
		strncpy(p + strlen(p), "/", 1);
		strcpy(p + strlen(p), gs_config.index_page);
	} else {
		len = strlen(gs_config.root) + len + 1;
		p = apr_memory_alloc(len);
		strncpy(p, gs_config.root, strlen(gs_config.root));
		strcpy(p + strlen(gs_config.root), uri);
		/* replace_token(p,'/','\\'); */
	}

	return p;
}

FILE *open_html_file(char *path) {
	FILE *p_html;
	p_html = fopen(path, "rb");
	return p_html;
}

int create_stream(char *s, response_info *p_info) {
	//char *t = apr_get_system_time();
	sprintf(s, "HTTP/1.1 %d %s \r\n", p_info->state, p_info->description);
	//sprintf(s+strlen(s),"Date:%s GMT \r\n",t);
	sprintf(s + strlen(s), "Server:iServer/0.01(linux) \r\n");
	if (p_info->state != 404) {
		sprintf(s + strlen(s), "Content-Length:%d \r\n", p_info->length);
		sprintf(s + strlen(s), "Content-Type:%s \r\n", p_info->type);
	}
	sprintf(s + strlen(s), "\r\n");

	//apr_memory_free(t);
	return strlen(s);
}

char *get_file_type(char *path) {
	int i = 0;
	char *s = strchr(path, '.');
	if (s == NULL)
		return "*/*";

	for (i = 0; i < POSTFIX; i++) {
		if (strcmp(s, postfix[i]) == 0)
			return html_t[i];
	}

	return "*/*";
}


char *response(request_t *p_request, long *len) {
	element *e;
	char *path, *html;
	response_info info;
	FILE *p_html;

	e = chained_hash_search(p_request->header, URI);
	if (e != NULL) {
		path = uri_map_path((char *) e->data);
		p_html = open_html_file(path);

		if (p_html == NULL) {
			html = apr_memory_alloc(RESP_HEADER_SIZ);
			info.state = 404;
			info.description = "Not Found";
			info.length = 0;
			info.type = "text/html";
			memset(html, 0, RESP_HEADER_SIZ);
			create_stream(html, &info);
			*len = RESP_HEADER_SIZ;
			return html;
		} else {
			int r = 0;
			long siz = apr_get_filesize(path);
			*len = RESP_HEADER_SIZ + siz + 10;
			html = apr_memory_alloc(*len);
			info.state = 200;
			info.description = "OK";
			info.length = siz;
			info.type = get_file_type(path);

			memset(html, 0, *len);
			r = create_stream(html, &info);
			fread(html + r, sizeof(char), siz, p_html);
		}

		apr_memory_free(path);
		fclose(p_html);
		return html;
	}
	return NULL;
}
