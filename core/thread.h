//
// Created by lishujun on 2/14/19.
//
#include "datatype.h"

#ifndef IHTTPD_FOR_LINUX_THREAD_H
#define IHTTPD_FOR_LINUX_THREAD_H

int create_work_thread(pf_thread p_thread_main, apr_thread_info *p_thread_info);

int thread_is_free(apr_thread_info *p_info);

int create_listen_thread(pf_thread p_thread_main, apr_thread_info *p_thread_info);

int create_allocate_thread(pf_thread p_thread_main, apr_thread_info *p_thread_info);

#endif //IHTTPD_FOR_LINUX_THREAD_H
