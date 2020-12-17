#include "global.h"

//共享段进程之间共享数据
#pragma data_seg("Shared")
#pragma data_seg()
#define __global __declspec(allocate("Shared"))

__global int DEBUG = TRUE;     //TRUE FALSE
__global apr_config gs_config;  //全局配置文件
__global int gs_workp_event; //子进程关闭事件句柄