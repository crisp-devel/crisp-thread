if   (NOT DEFINED PRESET_OS)
    message("[crisp-thread] Target OS is not defined.")
    message("[crisp-thread] thread feature requires OS preset definition.")
    message(SEND_ERROR)
endif()

if    (NOT DEFINED CRISP_INC)
    message("[crisp-thread] Thread Feature Requires crisp.")
    message(SEND_ERROR)
endif ()
if    (NOT DEFINED CRISP_SRC)
    message("[crisp-thread] Thread Feature Requires crisp.")
    message(SEND_ERROR)
endif ()

if   (PRESET_WIN32)
    lib                  (
        NAME crisp-thread
        SRC
        win32/thd.h
        win32/thd.c

        win32/mtx.h
        win32/mtx.c

        thd.h
        mut.h

        thread.h
        thread.c
    )
endif()

if   (PRESET_LINUX)
    lib                  (
        NAME crisp-thread
        SRC
        linux/thd.h
        linux/thd.c

        linux/mut.h
        linux/mut.c

        thd.h
        mut.h

        thread.h
        thread.c
    )
endif()

inc                           (
    crisp-thread-include
    ../include/thread/thd.h
    ../include/thread/mut.h
    ../include/thread.h
)

target_include_directories(crisp-thread PRIVATE ${CRISP_SRC})
set(CRISP_THREAD ON PARENT_SCOPE)