#include <memory.h>
#include <stdlib.h>
#include <windows.h>

//SRWLOCK LockAlloc;
//SRWLOCK only in WINDOWS 7 platform! 

void apr_memory_initialize()
{
	//InitializeSRWLock(&LockAlloc);
}

void *apr_memory_alloc(size_t size)
{
	void *p;
	//AcquireSRWLockShared(&LockAlloc);
	p = malloc(size);
	//ReleaseSRWLockShared(&LockAlloc);
	return p;
}

void apr_memory_free(void *p)
{
	//AcquireSRWLockShared(&LockAlloc);
	free(p);
	//ReleaseSRWLockShared(&LockAlloc);
}