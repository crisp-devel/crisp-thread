#ifndef THREAD_MUT_H
#define THREAD_MUT_H


#ifdef PRESET_LINUX
#include "linux/mut.h"
#endif

#ifdef PRESET_WIN32
#include "win32/mut.h"
#endif

#endif