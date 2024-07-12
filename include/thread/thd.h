#ifndef LINUX_THREAD_THD_H
#define LINUX_THREAD_THD_H

#include "core.h"

extern obj_trait *thd_t;
typedef struct    thd  { u8_t thd[128]; } thd;

fut* thd_fut(thd*);

#endif