set(RideShare_Headers
    passenger.hpp
    car.hpp
    station.hpp
    )

set(RideShare_Impl
    passenger.cpp
    car.cpp
    station.cpp
    )

add_library(RideShare_Objects OBJECT
    ${RideShare_Impl}
    )

target_include_directories(RideShare_Objects
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>    
    )

add_library(RideShare $<TARGET_OBJECTS:RideShare_Objects>)

add_library(RideShare::RideShare ALIAS RideShare)

set_target_properties(RideShare PROPERTIES
    CXX_EXTENSIONS NO
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    COMPILE_OPTIONS "-Wall -Wextra -Wpedantic -Werror -std=c++23"
    PUBLIC_HEADER "${RideShare_Headers}"
    )

target_compile_options(RideShare PRIVATE "-std=c++23")

include(GNUInstallDirs)

install(TARGETS RideShare RideShare_Objects
    EXPORT RideShare_Targets
    RUNTIME DESTINATION ${CMAKE_INSTAL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTAL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTAL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTAL_INCLUDEDIR}/src
    )

install(EXPORT RideShare_Targets
    FILE RideShare_Targets.cmake
    NAMESPACE RideShare::
    DESTINATION ${CMAKE_INSTAL_LIBDIR}/cmake/src
    )