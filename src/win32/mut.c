#include "mut.h"
#include <Windows.h>

static bool_t 
    do_new
        (mut* self, u32_t count, va_list arg)            {
            self->mut = CreateMutex(null_t, TRUE, null_t);
            return self->mut != INVALID_HANDLE_VALUE;
}

static bool_t 
    do_clone
        (mut* self, mut* clone) {
            return false_t;
}

static void
    do_del
        (mut* self)               {
            CloseHandle(self->mut);
}

static obj_trait 
    do_obj = make_trait (
        do_new     ,
        do_clone   ,
        null_t     ,
        do_del     ,
        sizeof(mut),
        null_t
);

obj_trait* mut_t = &do_obj;

bool_t 
    mut_lock_try
        (mut* self)                                    {
            if (trait_of(self) != mut_t) return false_t;
            return WaitForSingleObject(self->mut, 0) == WAIT_OBJECT_0;
}

void   
    mut_lock
        (mut* self)                                    {
            if (trait_of(self) != mut_t) return false_t;
            return WaitForSingleObject(self->mut, INFINITE);
}

void   
    mut_unlock
        (mut* self)                                     {
            if (trait_of (self) != mut_t) return false_t;
            ReleaseMutex(&self->mut);
}