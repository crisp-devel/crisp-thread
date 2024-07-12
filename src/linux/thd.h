#ifndef LINUX_THREAD_THD_H
#define LINUX_THREAD_THD_H

#include <core.h>
#include <pthread.h>

extern obj_trait *thd_t;
typedef struct    thd  {
    obj       head;
    void*   (*func)(void*);
    u64_t     stat;
    pthread_t thd ;
    void     *arg ;
    void     *ret ;
}   thd;

fut* thd_fut(thd*);

#endif