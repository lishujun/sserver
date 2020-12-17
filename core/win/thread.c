#include <windows.h>
#include "datatype.h"

int create_work_thread(pf_thread p_thread_main,apr_thread_info *p_thread_info)
{
	int thread;
	thread=apr_create_thread(p_thread_main,p_thread_info,CREATE_SUSPENDED);
	//p_thread_info->id     = GetThreadId(thread);  //GetThreadId() only in WINDOWS 7 platform! 
	p_thread_info->thread = thread;
	p_thread_info->state  = SUSPENDED;
	p_thread_info->socket = INVALID_SOCKET;
	p_thread_info->worked = apr_create_event(FALSE);
	p_thread_info->allocated = apr_create_event(FALSE);
	apr_resume_thread(p_thread_info->thread);
	return TRUE;
}

int create_listen_thread(pf_thread p_thread_main,apr_thread_info *p_thread_info)
{
	int thread;
	thread=apr_create_thread(p_thread_main,p_thread_info,CREATE_SUSPENDED);
	p_thread_info->thread = thread;
	apr_resume_thread(p_thread_info->thread);
	return TRUE;
}

int create_allocate_thread(pf_thread p_thread_main,apr_thread_info *p_thread_info)
{
	int thread;
	thread=apr_create_thread(p_thread_main,p_thread_info,CREATE_SUSPENDED);
	p_thread_info->thread = thread;
	apr_resume_thread(p_thread_info->thread);
	return TRUE;
}

int thread_is_free(apr_thread_info *p_info)
{
	if(apr_waiting_object(p_info->worked,0) == WAIT_OBJECT_0
			&& apr_waiting_object(p_info->allocated,0) != WAIT_OBJECT_0)
		return TRUE;
	else
		return FALSE;
}