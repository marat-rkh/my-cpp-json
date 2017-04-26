set(TEST_SRC simple-tests.cpp)
add_executable(simple-tests.test ${TEST_SRC})
target_link_libraries(simple-tests.test gtest_main json-parser)

set(TEST_SRC complex-tests.cpp)
add_executable(complex-tests.test ${TEST_SRC})
target_link_libraries(complex-tests.test gtest_main json-parser)