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

add_subdirectory(src)

add_subdirectory(exec)