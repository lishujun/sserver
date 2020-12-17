#include "datatype.h"
#include <stdio.h>

apr_config *read_config(apr_config *pconfig) {
	pconfig->port = 8484;
	pconfig->thread_number = 20;
	pconfig->socket_number = 1000;
	pconfig->root = "/usr/local/src/webroot";
	pconfig->index_page = "index.html";
	return pconfig;
}

