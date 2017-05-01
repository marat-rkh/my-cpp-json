#include "gtest/gtest.h"
 
#include "json_parser.h"

#include <iostream>

using namespace json_cpp;
using std::cout;
using std::endl;

TEST(json_parser, should_prcess_empty_object) {
    JsonParser parser;
    auto res = parser.Parse("data/empty_object.json");
    ASSERT_EQ(res->type(), ParseResult::Type::JSON);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}