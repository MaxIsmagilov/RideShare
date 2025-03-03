add_executable(RideShareTester RideShareTester.cpp)
target_include_directories(RideShareTester PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_link_libraries(RideShareTester PUBLIC RideShare)