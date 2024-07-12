#include "thd.h"
#include "../thread.h"

int do_run(mem*, int(*func)(any_t), any_t arg);

static void
    do_thd
        (thd* self)                              {
            if (trait_of(self) != thd_t) goto err;

            self->ret  = (any_t) do_run(null_t, self->func, self->arg);
            self->stat = fut_ready;
            return;

    err:    self->stat = fut_err;
            return;
}

static u64_t
    do_poll
        (thd* self)                                    {
            if (trait_of(self) != thd_t) return fut_err;
            return self->stat;
}

static any_t
    do_ret
        (thd* self)                                   {
            if (trait_of(self) != thd_t) return null_t;
            return self->ret;
}

static fut_ops
    do_fut = make_fut_ops (
        do_poll,
        do_ret
);

static bool_t
    do_new
        (thd* self, u32_t count, va_list par)                            {
            any_t func = null_t; if (count > 0) func = va_arg(par, any_t);
            any_t arg  = null_t; if (count > 1) arg  = va_arg(par, any_t);
            if (func == do_run) return false_t;
            if (!func)          return false_t;
            self->stat = fut_pend;
            self->func = func    ;
            self->arg  = arg     ;

            if (pthread_create(&self->thd, null_t, (void*(*)(void*))do_thd, self)) return false_t;
            return true_t;
}

static bool_t
    do_clone
        (thd* par, thd* par_clone) {
            return false_t;
}

static void
    do_del
        (thd* self)                        {
            pthread_join(self->thd, null_t);
}

static obj_trait
    do_obj = make_trait (
        do_new     ,
        do_clone   ,
        null_t     ,
        do_del     ,
        sizeof(thd),
        null_t
);

obj_trait *thd_t = &do_obj;

fut*
    thd_fut
        (thd* self)                                   {
            if (trait_of(self) != thd_t) return null_t;
            return make (fut) from (
                2      ,
                &do_fut,
                self
            );
}
