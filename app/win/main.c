#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "global.h"


void weclome()
{
	printf("iServer/0.01 Staring...\n");
	printf("Author is LiShujun,his email is icoding@qq.com\n\n");
}

int ap_mpm_run()
{
	char pid;

	weclome();
	pid = getenv("PARENT_ID");
	if(pid != NULL || DEBUG)
	{
		child_main();
	}
	// else
	// {
	// 	//暂时不会走此分支
	// 	master_main();
	// }
}

int __thread ui_main(void *param)
{
	char command[100];

	apr_thread_sleep(60);
	printf("Enter \"ShutDown\" to terminal server\n");
	do
	{
		printf("# ");
		scanf("%s",&command);
	}
	while(strcmp(command,"ShutDown")!=0);

	apr_set_event(gs_workp_event);
}

void server_initialize()
{
	int r;
	apr_memory_initialize();
	network_initialize();
	gs_workp_event = apr_create_event(FALSE);
	
	apr_create_thread(&ui_main,NULL,TRUE);
}


int main(int argc ,char *argv[])
{
	
	read_config(&gs_config);
	server_initialize();
	ap_mpm_run();
	return 0;
}