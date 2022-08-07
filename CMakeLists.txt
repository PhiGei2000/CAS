cmake_minimum_required(VERSION 3.0.0)
project(cas VERSION 0.1.0)

include(CTest)
enable_testing()

set(CXX_STANDARD 20)

include_directories(./include)

include(sourcelist.cmake)

add_executable(cas ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
