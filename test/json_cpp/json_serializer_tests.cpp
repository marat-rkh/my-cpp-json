#include "gtest/gtest.h"

#include "json_cpp.h"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::stringstream;
using std::string;

using namespace json_cpp;

void ShouldPrint(string const &in_file, string const &pretty_file, string const &compact_file) {
    stringstream buffer;

    ifstream ifs(pretty_file);
    buffer << ifs.rdbuf();
    ifs.close();
    auto pretty = buffer.str();
    buffer.str("");

    ifs.open(compact_file);
    buffer << ifs.rdbuf();
    ifs.close();
    auto compact = buffer.str();
    buffer.str("");

    JsonParser parser;
    auto json = parser.Parse(in_file);

    JsonSerializer jser;
    ASSERT_EQ(jser.PrettyPrint(json), pretty);
    ASSERT_EQ(jser.CompactPrint(json), compact);
}

TEST(json_serializer, should_print_empty_object) {
    auto json = Json::obj();
    JsonSerializer jser;
    ASSERT_EQ(jser.PrettyPrint(json), "{\n}");
    ASSERT_EQ(jser.CompactPrint(json), "{}");
}

TEST(json_serializer, DISABLED_should_print_all_field_types_json) {
    ShouldPrint(
        "data/all_field_types.json", 
        "data/all_field_types_pretty.json", 
        "data/all_field_types_compact.json"
    );
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}