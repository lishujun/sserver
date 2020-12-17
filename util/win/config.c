#include "datatype.h"
#include <stdio.h>

/*
   从配置文件读取配置，该代码未实现，但是以 apr_config作为接口，此部分代码可以先不予实现
*/
apr_config *read_config(apr_config *pconfig)
{
	pconfig->port= 8484;
	pconfig->thread_number = 20;
	pconfig->socket_number = 1000;
	pconfig->root = "D:\\inetpub\\wwwroot";
	pconfig->index_page = "index.html";
	return pconfig;
}

