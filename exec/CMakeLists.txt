add_executable(RideShareRunner RideShareRunner.cpp)
target_include_directories(RideShareRunner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_link_libraries(RideShareRunner PUBLIC RideShare)