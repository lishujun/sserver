#include "datatype.h"
#include "api.h"
#include <sys/stat.h>

int apr_create_semaphore(apr_thread_semaphore *p_semaphore, int size) {
#define ONE_PROCESS   0
#define PROCESS_SHARE 1
	return sem_init(p_semaphore, ONE_PROCESS, size);
}

int apr_wait_semaphore(apr_thread_semaphore *p_semaphore) {
	return sem_wait(p_semaphore);
}

int apr_signal_semaphore(apr_thread_semaphore *p_semaphore) {
	return sem_post(p_semaphore);
}

int apr_destroy_semaphore(apr_thread_semaphore *p_semaphore) {
	return sem_destroy(p_semaphore);
}

int apr_create_mutex(apr_thread_mutex *p_mutex) {
	int r = -1;
	r = pthread_mutex_init(p_mutex, NULL);
	return r;
}

int apr_check_mutex(apr_thread_mutex *p_mutex) {
	if (pthread_mutex_trylock(p_mutex) == 0)
		return TRUE;
	else
		return FALSE;
}

int apr_wait_mutex(apr_thread_mutex *p_mutex) {
	return pthread_mutex_lock(p_mutex);
}

int apr_signal_mutex(apr_thread_mutex *p_mutex) {
	return pthread_mutex_unlock(p_mutex);
}

int apr_destroy_mutex(apr_thread_mutex *p_mutex) {
	return pthread_mutex_destroy(p_mutex);
}

int apr_create_cond(void *cond) {
	return pthread_cond_init(cond, NULL);
}

int apr_destroy_cond(void *cond) {
	return pthread_cond_destroy(cond);
}

int apr_signal_cond(void *cond) {
	return pthread_cond_signal(cond);
}

int apr_set_and_wait(void *s_object, void *w_object) {
	return pthread_cond_wait(w_object, s_object);
}

int apr_create_thread(apr_thread_t *pt, pf_thread pf_main, void *arg) {
	int r;
	r = pthread_create(pt, NULL, pf_main, arg);
	return r;
}

/*it's going to suspend caller*/
int apr_suspend_thread(apr_thread_mutex *p_mutex) {
	pthread_mutex_trylock(p_mutex);
	pthread_mutex_lock(p_mutex);
}

int apr_resume_thread(apr_thread_mutex *p_mutex) {
	return pthread_mutex_unlock(p_mutex);
}


void apr_thread_sleep(float second) {
	usleep(1000 * second);
}

long apr_get_filesize(char *filename) {

	struct stat f_stat;
	if (stat(filename, &f_stat) == -1) {
		return -1;
	}
	return (long) f_stat.st_size;
}


/*
char *apr_get_system_time()
{

}
*/
