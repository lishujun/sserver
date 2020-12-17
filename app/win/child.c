#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <windows.h>
#include "datatype.h"
#include "global.h"

#define SPAN 100
#define TRYMAX 3

apr_server_state g_child_state;
apr_socket_queue queue;
apr_thread_info *g_threads = NULL; /*工作线程管理结构*/
apr_thread_manager g_manager;      /*系统维护线程管理结构*/

int __thread work_main(void *param)
{
	apr_thread_info *p_info;
	request_t *p_request = NULL;
	char *pb1 = apr_memory_alloc(REQ_BUF_SIZ),*pb2 = NULL;
	// __try
	// {
		p_info = (apr_thread_info*)param;
		for(;g_child_state == START;)
		{
			if(p_info->socket != INVALID_SOCKET)//thread is working
			{
				int r = 0;
				memset(pb1,0,REQ_BUF_SIZ);
				r = apr_socket_recv(p_info->socket,pb1,REQ_BUF_SIZ);
				if(r != SOCKET_ERROR && r != 0)
				{
					int len = 0;
					create_request_structure(&p_request);
					read_request(p_request,pb1,r);
					pb2 = response(p_request,&len);
					apr_socket_send(p_info->socket,pb2,len+1);
					apr_socket_close(p_info->socket);
					apr_memory_free(pb2);
					destroy_request_structure(&p_request);
				}
				
			}
			p_info->socket = INVALID_SOCKET;
			p_info->state  = SUSPENDED;
			apr_set_and_wait(p_info->worked,p_info->allocated);// the thread is free
		}
		apr_memory_free(pb1);
	// }
	// __except(EXCEPTION_EXECUTE_HANDLER)
	// {
	// 	p_info->state = STOP;
	// 	apr_memory_free(pb1);
	// 	return;
	// }
}


int __thread listen_main(void *param)
{
	int i,socket;
	for(;g_child_state == START;)
	{
		socket = (int)apr_socket_accept();
		if(enqueue(&queue,socket)!= TRUE)
		{
			continue;
			//drop it
		}
	}
}


int __thread allocate_main(void *param)
{
	volatile int i = 0;
	volatile int socket;
	for(;g_child_state == START;)
	{
		dequeue(&queue,&socket);
		for(;i <= gs_config.thread_number;i++)
		{
			if(i >= gs_config.thread_number)
				i = 0;

			if(thread_is_free(&g_threads[i]))
			{
				g_threads[i].state = RUN;
				g_threads[i].socket = socket;
				apr_reset_event(g_threads[i].worked);
				apr_pulse_event(g_threads[i].allocated);
				i++;
				break;
			}
		}
	}
}

void child_main()
{
	int i = 0,r;


	g_child_state = START;
	g_threads = (apr_thread_info *)apr_memory_alloc(sizeof(apr_thread_info)*gs_config.thread_number);
	for(i = 0;i<gs_config.thread_number;i++)
	{
		create_work_thread(&work_main,&g_threads[i]);
	}

	create_queue(&queue,&gs_config);
	create_listen_thread(&listen_main,&g_manager.listener);
	create_allocate_thread(&allocate_main,&g_manager.allocator);

	//the child process will return
	r = apr_waiting_object((HANDLE)gs_workp_event,INFINITE);
	if(r == WAIT_OBJECT_0)
	{
		//g_child_event = SHUTDOWN;
		InterlockedExchangeAdd(&g_child_state,1);
		Sleep(1000*5);
		return;
	}
}