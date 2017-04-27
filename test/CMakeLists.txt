set(TEST_SRC json_value_tests.cpp)
add_executable(json_value.test ${TEST_SRC})
target_link_libraries(json_value.test gtest_main json-cpp)

set(TEST_SRC lexer_tests.cpp)
add_executable(lexer.test ${TEST_SRC})
target_link_libraries(lexer.test gtest_main json-cpp)