include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

macro   (crisp_thread_examples)
    add_subdirectory(lib/crisp-thread/examples)
endmacro()