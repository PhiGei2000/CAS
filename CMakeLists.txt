cmake_minimum_required(VERSION 3.20.0)
project(cas VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -stdlib=libc++)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
add_compile_definitions(DEBUG)
endif()

if (MSVC)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

add_subdirectory(mathlib)

include_directories(./include)

file(GLOB_RECURSE SOURCES ./src/**.cpp)

add_executable(cas ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)
set_property(TARGET cas PROPERTY ENABLE_EXPORTS 1)

target_link_libraries(cas PUBLIC mathlib)
target_include_directories(cas PUBLIC mathlib/include)

# add_subdirectory(test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


