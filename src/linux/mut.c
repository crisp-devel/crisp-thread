#include "mut.h"

static bool_t
    do_new
        (mut* self, u32_t count, va_list arg)                 {
            return pthread_mutex_init(&self->mut, null_t) == 0;
}

static bool_t
    do_clone
        (mut* self, mut* clone) {
            return false_t;
}

static void
    do_del
        (mut* self)                          {
            pthread_mutex_destroy(&self->mut);
}

static obj_trait do_obj = make_trait (
    do_new     ,
    do_clone   ,
    null_t     ,
    do_del     ,
    sizeof(mut),
    null_t
);

obj_trait *mut_t = &do_obj;

bool_t
    mut_lock_try
        (mut* self)                                              {
            if (trait_of(self) != mut_t)           return false_t;
            if (pthread_mutex_trylock(&self->mut)) return false_t;
            return true_t;
}

bool_t
    mut_lock
        (mut* self)                                    {
            if (trait_of(self) != mut_t) return false_t;
            pthread_mutex_lock(&self->mut);
            return true_t;

}

void
    mut_unlock
        (mut* self)                            {
            if (trait_of(self) != mut_t) return;
            pthread_mutex_unlock(&self->mut);
}