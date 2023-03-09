cmake_minimum_required(VERSION 3.23.0)
project(mathlib VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 23)

include_directories(./include)

file(GLOB_RECURSE SOURCES ./src/**.cpp)

add_library(mathlib SHARED ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

set_target_properties(mathlib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER ./include/mathlib.hpp)

target_include_directories(mathlib PRIVATE ./include)
target_include_directories(mathlib PRIVATE ./src)

install(TARGETS mathlib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
