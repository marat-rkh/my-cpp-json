set(TEST_SRC json_value_tests.cpp)
add_executable(json_value.test ${TEST_SRC})
target_link_libraries(json_value.test gtest_main json-cpp)