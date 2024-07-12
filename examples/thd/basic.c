#include "thread.h"
#include "core.h"

use (dep (thread))

void test_1 ()             {
    println("Hello Thread");
}

int run ()                                          {
    thd* thd_1 = make (thd) from (2, test_1, null_t);
    mut* mut_1 = make (mut) from (0);

    del (thd_1);
}