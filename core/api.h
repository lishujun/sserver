#ifndef __API

#define __API

int apr_create_semaphore(apr_thread_semaphore *p_semaphore, int size);

int apr_wait_semaphore(apr_thread_semaphore *p_semaphore);

int apr_signal_semaphore(apr_thread_semaphore *p_semaphore);

int apr_destroy_semaphore(apr_thread_semaphore *p_semaphore);

int apr_create_mutex(apr_thread_mutex *p_mutex);

int apr_check_mutex(apr_thread_mutex *p_mutex);

int apr_wait_mutex(apr_thread_mutex *p_mutex);

int apr_signal_mutex(apr_thread_mutex *p_mutex);

int apr_destroy_mutex(apr_thread_mutex *p_mutex);

int apr_create_cond(void *cond);

int apr_destroy_cond(void *cond);

int apr_signal_cond(void *cond);

int apr_set_and_wait(void *s_object, void *w_object);

int apr_create_thread(apr_thread_t *pt, pf_thread pf_main, void *arg);

int apr_suspend_thread(apr_thread_mutex *p_mutex);

int apr_resume_thread(apr_thread_mutex *p_mutex);

void apr_thread_sleep(float second);

long apr_get_filesize(char *filename);

#endif