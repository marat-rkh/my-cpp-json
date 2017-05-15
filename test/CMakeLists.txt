set(TEST_SRC json_tests.cpp)
add_executable(json.test ${TEST_SRC})
target_link_libraries(json.test gtest_main json-cpp)

set(TEST_SRC lexer_tests.cpp)
add_executable(lexer.test ${TEST_SRC})
target_link_libraries(lexer.test gtest_main json-cpp)

set(TEST_SRC json_parser_tests.cpp)
add_executable(json_parser.test ${TEST_SRC})
target_link_libraries(json_parser.test gtest_main json-cpp)

set(TEST_SRC json_serializer_tests.cpp)
add_executable(json_serializer.test ${TEST_SRC})
target_link_libraries(json_serializer.test gtest_main json-cpp)

set(TEST_SRC ordered_hashmap_tests.cpp)
add_executable(ordered_hashmap.test ${TEST_SRC})
target_link_libraries(ordered_hashmap.test gtest_main json-cpp)

set(TEST_SRC mapping_iterator_tests.cpp)
add_executable(mapping_iterator.test ${TEST_SRC})
target_link_libraries(mapping_iterator.test gtest_main json-cpp)