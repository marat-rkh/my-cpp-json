#include "gtest/gtest.h"
#include "mapping_iterator.h"

#include <vector>
#include <functional>
#include <map>

using namespace json_cpp::inner::utils;
using std::vector;
using std::function;
using std::map;
using std::pair;

TEST(mapping_iterator, should_return_by_value) {
    vector<int> vs = {1, 2, 3};
    function<int(int&)> x2 = [](int &v)-> int { return v * 2; };
    auto it = MakeMappingBegin(vs.begin(), x2);
    auto end = MakeMappingEnd(vs.end(), x2);
    ASSERT_EQ(*it++, 2);
    ASSERT_EQ(*it++, 4);
    ASSERT_EQ(*it++, 6);
    ASSERT_EQ(it, end);
}

TEST(mapping_iterator, should_use_closure) {
    vector<int> vs = {1, 2, 3};
    map<int, int> ms = {
        {1, 2},
        {2, 4},
        {3, 6}
    };
    auto get = [&ms](int &v)-> pair<const int, int> &{ return *ms.find(v); };
    auto it = MakeMappingBegin(vs.begin(), get);
    auto end = MakeMappingEnd(vs.end(), get);
    ASSERT_EQ(*it++, *ms.find(1));
    ASSERT_EQ(*it++, *ms.find(2));
    ASSERT_EQ(*it++, *ms.find(3));
    ASSERT_EQ(it, end);
}

TEST(mapping_iterator, should_return_by_reference) {
    vector<int> vs = {1, 2, 3};
    map<int, int> ms = {
        {1, 2},
        {2, 4},
        {3, 6}
    };
    auto get = [&ms](int &v)-> int&{ return ms[v]; };
    for(auto it = MakeMappingBegin(vs.begin(), get); it != MakeMappingEnd(vs.end(), get); ++it) {
        *it *= 10;
    }
    auto it = ms.begin();
    ASSERT_EQ((it++)->second, 20);
    ASSERT_EQ((it++)->second, 40);
    ASSERT_EQ((it++)->second, 60);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}