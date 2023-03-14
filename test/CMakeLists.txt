add_executable(parser_test parser.cpp ../src/io/parser.cpp)
target_link_libraries(parser_test PRIVATE mathlib)

target_include_directories(parser_test PRIVATE ../include)
target_include_directories(parser_test PRIVATE ../mathlib/include)

add_test(NAME parser COMMAND parser_test)