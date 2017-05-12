#include "gtest/gtest.h"
#include "ordered_hashmap.h"

#include <vector>
#include <string>

using namespace json_cpp::inner::utils;
using std::vector;
using std::string;
using std::pair;
using std::initializer_list;

template class OrderedHashMap<string, int>;

void AssertOrdered(
    OrderedHashMap<string, int> const &map, 
    initializer_list<pair<string, int>> const &order
) {
    vector<pair<string, int>> expected(order);
    vector<pair<string, int>> actual;
    for(auto &e: map) {
        actual.push_back(e);
    }
    ASSERT_EQ(actual, expected);
}

TEST(ordered_hashmap, should_be_in_order1) {
    OrderedHashMap<string, int> map = {
        {"a", 4},
        {"z", 2},
        {"b", 1},
        {"o", 3},
        {"e", 5}
    };
    AssertOrdered(map, {{"a", 4}, {"z", 2}, {"b", 1}, {"o", 3}, {"e", 5}});
}

TEST(ordered_hashmap, should_be_in_order2) {
    OrderedHashMap<string, int> map;
    map["a"] = 4;
    map["z"] = 2;
    map["b"] = 1;
    map["o"] = 3;
    map["e"] = 5;
    AssertOrdered(map, {{"a", 4}, {"z", 2}, {"b", 1}, {"o", 3}, {"e", 5}});
}

TEST(ordered_hashmap, should_be_modified_through_iterator) {
    OrderedHashMap<string, int> map{
        {"a", 4},
        {"z", 2},
        {"b", 1}
    };
    for(auto &e: map) {
        e.second *= 10;
    }
    AssertOrdered(map, {{"a", 40}, {"z", 20}, {"b", 10}});
}

TEST(ordered_hashmap, should_shrink_to_fit_on_erase) {
    OrderedHashMap<string, int> map = {
        {"a", 4},
        {"z", 2},
        {"b", 1},
        {"o", 3},
        {"e", 5}
    };
    map.erase("z");
    map.erase("b");
    map.erase("e");
    ASSERT_EQ(map.shrink_to_fit(), 0U);
    AssertOrdered(map, {{"a", 4}, {"o", 3}});
}

TEST(ordered_hashmap, should_shrink_to_fit) {
    OrderedHashMap<string, int> map = {
        {"a", 4},
        {"z", 2},
        {"b", 1},
        {"o", 3},
        {"e", 5}
    };
    map.erase("z");
    map.erase("b");
    ASSERT_EQ(map.shrink_to_fit(), 2U);
    AssertOrdered(map, {{"a", 4}, {"o", 3}, {"e", 5}});
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}