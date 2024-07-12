#ifndef LINUX_THREAD_MUT_H
#define LINUX_THREAD_MUT_H

#include <core.h>
#include <pthread.h>

extern obj_trait *mut_t ;
typedef struct    mut   {
    obj             head;
    pthread_mutex_t mut ;
}   mut;

bool_t mut_lock_try(mut*);
bool_t mut_lock    (mut*);
void   mut_unlock  (mut*);

#define sync_all(mut) for(bool_t i = true_t ; i && mut_lock((mut)) ; i = false_t, mut_unlock(mut))

#endif