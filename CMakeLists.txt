cmake_minimum_required(VERSION 3.12.0)
project(cas VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(./include)

include(sourcelist.cmake)

add_executable(cas ${SOURCES})
target_link_libraries(cas ${GTK4_LIBRARIES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
