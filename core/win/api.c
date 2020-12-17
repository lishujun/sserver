#include <windows.h>
#include <sys/stat.h>
#include "datatype.h"


//等待API封装
int apr_waiting_object(int object,int msec)
{
	int r;
	r = WaitForSingleObject((HANDLE)object,msec);//INFINITE is never
	return r;
}

int apr_waiting_objects(int* objects,int msec)
{
	//return WaitForSingleObject(((HANDLE)signal,INFINITE);
}

int apr_set_and_wait(int s_object,int w_object)
{
	return SignalObjectAndWait((HANDLE)s_object,(HANDLE)w_object,INFINITE,FALSE);
}

//线程API封装
int apr_create_thread(pf_thread pf_main,void *arg,int state)
{
	HANDLE thread = CreateThread(NULL,0,pf_main,arg,state,NULL);
	return thread;
}

int apr_suspend_thread(int thread)
{
	int r;
	r = SuspendThread(thread);
	return r;
}

int apr_resume_thread(int thread)
{
	int r;
	r = ResumeThread(thread);
	return r;
}

int apr_thread_sleep(float second)
{
	Sleep(1000*second);
}

thread_state apr_thread_state(int thread)
{
	int state;
	if(GetExitCodeThread((HANDLE)thread,&state)==TRUE)
	{
		if(state == STILL_ACTIVE)
			return RUN;
		else
			return STOP;
	}
	return STOP;
}

//事件API封装
int apr_create_event(int state)
{
	HANDLE ex;
	ex = CreateEvent(NULL,FALSE,state,NULL);
	return ex;
}

int apr_reset_event(int ex)
{
	return ResetEvent((HANDLE)ex);
}

int apr_set_event(int ex)
{
	return SetEvent((HANDLE)ex);
}

int apr_wait_event(int ex,int msec)
{
	return apr_waiting_object(ex,msec);
}

int apr_pulse_event(int ex)
{
	return PulseEvent((HANDLE)ex);
}


//信号量API封装

int apr_create_mutex(int size,int max)
{
	HANDLE r;
	r = CreateSemaphore(NULL,size,max,NULL);
	if(r == NULL || r == INVALID_HANDLE_VALUE)
	{
		printf("create mutex...\n");
	}
	return r;
}

int apr_wait_mutex(int mutex,int msec)
{
	return apr_waiting_object(mutex,msec);
}

int apr_signal_mutex(int mutex)
{
	return ReleaseSemaphore(mutex,1,NULL);
}

//封装文件操作的一些特殊方法
long apr_get_filesize(char *filename)
{
    struct stat     f_stat;
    if (stat(filename, &f_stat) == -1) 
    {
        return -1;
    }
    return (long)f_stat.st_size;
}

//时间API

char *apr_get_system_time()
{
	char *p;
	SYSTEMTIME t1;
	GetLocalTime(&t1);
	p = apr_memory_alloc(100);
	if(p != NULL)
	{
		sprintf(p,"%d/%d/%d %d:%d:%d",t1.wYear,t1.wMonth,t1.wDay,t1.wHour,t1.wMinute,t1.wSecond);
	}

	return p;
}

//进程操作的API

int apr_get_current_pid()
{
	return GetCurrentProcessId();
}

int apr_create_process(wchar_t *app ,char *env_variable,
							STARTUPINFO *si,PROCESS_INFORMATION *pi)
{
	SECURITY_ATTRIBUTES SA;
	SA.nLength = sizeof(SA);
	SA.lpSecurityDescriptor = NULL;
	SA.bInheritHandle = TRUE;
	return CreateProcess(NULL,app,&SA,NULL,TRUE,0,env_variable,NULL,si,pi);
}