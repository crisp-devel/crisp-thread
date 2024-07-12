include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

if   (NOT CRISP_TLS)
    message("[crisp-thread] crisp-thread requires CRISP_TLS option for thread local storage support.")
    message(SEND_ERROR)
endif()

macro   (crisp_thread_examples)
    add_subdirectory(lib/crisp-thread/examples)
endmacro()