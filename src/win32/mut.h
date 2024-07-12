#ifndef THREAD_WIN32_MUT_H
#define THREAD_WIN32_MUT_H

#include <core.h>

extern obj_trait *mut_t;
typedef struct    mut  {
    obj   head;
    any_t mut ;
}   mut;

bool_t mut_lock_try(mut*);
void   mut_lock    (mut*);
void   mut_unlock  (mut*);

#endif