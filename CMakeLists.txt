cmake_minimum_required(VERSION 3.25)

project(
    RideShare
    VERSION 0.0.0
    LANGUAGES C CXX
    )

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 23)
add_compile_options(-std=c++23)

if(NOT WIN32)
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-lpthread" COMPILER_SUPPORTS_THREADS)

    if (COMPILER_SUPPORTS_THREADS)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")
    else ()
        message(FATAL_ERROR "Your compiler does not support C++ threads")
    endif ()
endif ()

add_subdirectory(src)

add_subdirectory(exec)