//
// Created by lishujun on 2/14/19.
//

#ifndef IHTTPD_FOR_LINUX_CHILD_H
#define IHTTPD_FOR_LINUX_CHILD_H

void *work_main(void *param);

void *listen_main(void *param);

void *allocate_main(void *param);

void child_main();

#endif //IHTTPD_FOR_LINUX_CHILD_H
