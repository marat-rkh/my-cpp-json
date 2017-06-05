set(TEST_SRC my_cpp_json/json_tests.cpp)
add_executable(json.test ${TEST_SRC})
target_link_libraries(json.test gtest_main my-cpp-json)

set(TEST_SRC my_cpp_json/internal/lexer/lexer_tests.cpp)
add_executable(lexer.test ${TEST_SRC})
target_link_libraries(lexer.test gtest_main my-cpp-json)

set(TEST_SRC my_cpp_json/json_parser_tests.cpp)
add_executable(json_parser.test ${TEST_SRC})
target_link_libraries(json_parser.test gtest_main my-cpp-json)

set(TEST_SRC my_cpp_json/json_serializer_tests.cpp)
add_executable(json_serializer.test ${TEST_SRC})
target_link_libraries(json_serializer.test gtest_main my-cpp-json)

set(TEST_SRC my_cpp_json/internal/utils/ordered_hashmap_tests.cpp)
add_executable(ordered_hashmap.test ${TEST_SRC})
target_link_libraries(ordered_hashmap.test gtest_main my-cpp-json)

set(TEST_SRC my_cpp_json/internal/utils/mapping_iterator_tests.cpp)
add_executable(mapping_iterator.test ${TEST_SRC})
target_link_libraries(mapping_iterator.test gtest_main my-cpp-json)