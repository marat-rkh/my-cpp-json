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

TEST(json_parser, should_handle_top_level_array) {
    JsonParser parser;
    auto res = parser.Parse("data/top_level_array.json");
    ASSERT_EQ(res->type(), ParseResult::Type::JSON);
    Json arr = as<ParsedJson>(res)->value();
    ASSERT_EQ(arr[0].AsDouble(), 1.0);
    ASSERT_EQ(arr[1].AsDouble(), 2.0);
    ASSERT_EQ(arr[2].AsDouble(), 3.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}