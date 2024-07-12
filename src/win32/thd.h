#ifndef THREAD_WIN32_THD_H
#define THREAD_WIN32_THD_H

#include <core.h>

extern obj_trait *thd_t;
typedef struct    thd  {
    obj    head;
    void*(*func)(void*);
    u64_t  stat;
    any_t  thd;
    void*  arg;
    void*  ret;
}   thd;

fut* thd_fut(thd*);

#endif