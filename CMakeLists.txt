cmake_minimum_required(VERSION 3.20.0)
project(cas VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(mathlib)

include_directories(./include)

file(GLOB_RECURSE SOURCES ./src/**.cpp)

add_executable(cas ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

target_link_libraries(cas PUBLIC mathlib)
target_include_directories(cas PUBLIC mathlib/include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
