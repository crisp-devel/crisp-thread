#ifndef THREAD_THD_H
#define THREAD_THD_H

#ifdef PRESET_LINUX
#include "linux/thd.h"
#endif

#ifdef PRESET_WIN32
#include "win32/thd.h"
#endif

#endif