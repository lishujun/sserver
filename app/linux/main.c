#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "datatype.h"
#include "global.h"
#include "child.h"
#include "api.h"
#include "memory.h"
#include "config.h"
#include "listen.h"


void weclome() {
	printf("iServer/0.01 Staring...\n");
	printf("Author is Dennis Li,his email is icoding@qq.com\n\n");
}

int ap_mpm_run() {
	char *pid;
	pid = getenv("PARENT_ID");
	if (pid != NULL || DEBUG) {
		child_main();
	}
	//else
	//{
	//	master_main();
	//}
}

void *ui_main(void *param) {
	char command[100];

	apr_thread_sleep(60);
	printf("Enter \"ShutDown\" to terminal server\n");
	do {
		printf("# ");
		scanf("%s", &command);
	} while (strcmp(command, "ShutDown") != 0);

	apr_resume_thread(&svr_shutd);
}

void server_initialize() {
	int r;
	apr_thread_t pt;
	apr_memory_initialize();
	r = network_initialize();
	if (r == FALSE) {
		char *msg = strerror(errno);
		printf(msg);
		exit(-1);
	}

	apr_create_thread(&pt, &ui_main, NULL);
	apr_create_mutex(&svr_shutd);
}


int main(int argc, char *argv[]) {
	weclome();
	read_config(&gs_config);
	server_initialize();
	ap_mpm_run();
	return 0;
}
