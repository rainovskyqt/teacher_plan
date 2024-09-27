#set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON" FORCE)

if(UNIX)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(ASAN ON)
    endif ()
endif()

add_compile_options(-Wall -Wextra)

if (ASAN)
    message(STATUS "ASAN enabled")
    add_compile_options(-fsanitize=address)
endif()

macro(global_flags_set_project)
    if (ASAN)
        target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
    endif()
endmacro()
