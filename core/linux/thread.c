#include "datatype.h"
#include "api.h"

int create_work_thread(pf_thread p_thread_main, apr_thread_info *p_thread_info) {
	p_thread_info->state = RUN;
	p_thread_info->socket = INVALID_SOCKET;
	apr_create_mutex(&p_thread_info->worked);
	apr_create_cond(&p_thread_info->allocated);
	apr_create_thread(&(p_thread_info->thread), p_thread_main, p_thread_info);

	return TRUE;
}

int thread_is_free(apr_thread_info *p_info) {
	if (p_info->state == SUSPENDED
		&& apr_check_mutex(&p_info->worked) == TRUE) {
		apr_signal_mutex(&p_info->worked);
		return TRUE;
	} else
		return FALSE;
}


int create_listen_thread(pf_thread p_thread_main, apr_thread_info *p_thread_info) {
	apr_create_thread(&p_thread_info->thread, p_thread_main, p_thread_info);
	return TRUE;
}

int create_allocate_thread(pf_thread p_thread_main, apr_thread_info *p_thread_info) {
	apr_create_thread(&p_thread_info->thread, p_thread_main, p_thread_info);
	return TRUE;
}
