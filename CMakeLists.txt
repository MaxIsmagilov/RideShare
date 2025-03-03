cmake_minimum_required(VERSION 3.25)

project(
    RideShare
    VERSION 0.0.0
    LANGUAGES C CXX
    )

add_subdirectory(src)

add_subdirectory(exec)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "{CMAKE_CXX_FLAGS} -std=c++23")
