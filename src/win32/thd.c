#include "thd.h"
#include <Windows.h>

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

static void*
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
        (thd* self, u32_t par_count, va_list par)                            {
            void* func = null_t; if (par_count > 0) func = va_arg(par, void*);
            void* arg  = null_t; if (par_count > 1) arg  = va_arg(par, void*);
            if (!func) return false_t;
            self->stat = fut_pend;
            self->func = func    ;
            self->arg  = arg     ;
            self->thd  = CreateThread (
                null_t,
                0     ,
                do_thd,
                self  ,
                0     ,
                null_t
            );

            return self->thd != INVALID_HANDLE_VALUE;
}

static bool_t
    do_clone
        (thd* self, thd* clone) {
            return false_t;
}

static void
    do_del
        (thd* self)                                 {
            WaitForSingleObject(self->thd, INFINITE);
            CloseHandle        (self->thd);
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

obj_trait* thd_t = &do_obj;

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