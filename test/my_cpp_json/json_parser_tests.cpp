#include "gtest/gtest.h"
 
#include "my_cpp_json.h"

#include <iostream>

using std::cout;
using std::endl;

using namespace my_cpp_json;

TEST(json_parser, should_prcess_empty_object) {
    JsonParser parser;
    Json json = parser.Parse("data/empty_object.json");
    ASSERT_EQ(json.Type(), JType::JOBJECT);
}

TEST(json_parser, should_handle_top_level_array) {
    JsonParser parser;
    Json arr = parser.Parse("data/top_level_array.json");
    ASSERT_EQ(arr[0].AsDouble(), 1.0);
    ASSERT_EQ(arr[1].AsDouble(), 2.0);
    ASSERT_EQ(arr[2].AsDouble(), 3.0);
}

TEST(json_parser, should_handle_all_field_types) {
    JsonParser parser;
    Json obj = parser.Parse("data/all_field_types.json");

    ASSERT_EQ(obj["str_field"].AsString(), "str_value");
    ASSERT_EQ(obj["arr_field"][0].AsDouble(), 1.0);
    ASSERT_EQ(obj["arr_field"][1].AsDouble(), 2.0);
    ASSERT_EQ(obj["num_field"].AsDouble(), -123.4);
    ASSERT_EQ(obj["null_field"].Type(), JType::JNULL);
    ASSERT_EQ(obj["obj_field"].Type(), JType::JOBJECT);
}

TEST(json_parser, should_parse_real_world1_json) {
    JsonParser parser;
    Json obj = parser.Parse("data/real_world1.json");

    ASSERT_EQ(obj["glossary"]["title"].AsString(), "example glossary");
    ASSERT_EQ(obj["glossary"]["GlossDiv"]["title"].AsString(), "S");
    ASSERT_EQ(obj["glossary"]["GlossDiv"]["GlossList"]["GlossEntry"]["ID"].AsString(), "SGML");
    ASSERT_EQ(obj["glossary"]["GlossDiv"]["GlossList"]["GlossEntry"]["SortAs"].AsString(), "SGML");
    ASSERT_EQ(obj["glossary"]["GlossDiv"]["GlossList"]["GlossEntry"]["GlossTerm"].AsString(), 
        "Standard Generalized Markup Language");
    ASSERT_EQ(obj["glossary"]["GlossDiv"]["GlossList"]["GlossEntry"]["Acronym"].AsString(), "SGML");
    ASSERT_EQ(obj["glossary"]["GlossDiv"]["GlossList"]["GlossEntry"]["Abbrev"].AsString(), "ISO 8879:1986");
    ASSERT_EQ(obj["glossary"]["GlossDiv"]["GlossList"]["GlossEntry"]["GlossDef"]["para"].AsString(), 
        "A meta-markup language, used to create markup languages such as DocBook.");
    ASSERT_EQ(obj["glossary"]["GlossDiv"]["GlossList"]["GlossEntry"]["GlossDef"]["GlossSeeAlso"][0].AsString(), 
        "GML");
    ASSERT_EQ(obj["glossary"]["GlossDiv"]["GlossList"]["GlossEntry"]["GlossDef"]["GlossSeeAlso"][1].AsString(), 
        "XML");
}

TEST(json_parser, should_parse_real_world2_json) {
    JsonParser parser;
    Json obj = parser.Parse("data/real_world2.json");

    ASSERT_EQ(obj["widget"]["debug"].AsString(), "on");
    ASSERT_EQ(obj["widget"]["window"]["title"].AsString(), "Sample Konfabulator Widget");
    ASSERT_EQ(obj["widget"]["window"]["name"].AsString(), "main_window");
    ASSERT_EQ(obj["widget"]["window"]["width"].AsDouble(), 500.0);
    ASSERT_EQ(obj["widget"]["window"]["height"].AsDouble(), 500.0);
    ASSERT_EQ(obj["widget"]["image"]["src"].AsString(), "Images/Sun.png");
    ASSERT_EQ(obj["widget"]["image"]["name"].AsString(), "sun1");
    ASSERT_EQ(obj["widget"]["image"]["hOffset"].AsDouble(), 250.0);
    ASSERT_EQ(obj["widget"]["image"]["vOffset"].AsDouble(), 250.0);
    ASSERT_EQ(obj["widget"]["image"]["alignment"].AsString(), "center");
    ASSERT_EQ(obj["widget"]["text"]["data"].AsString(), "Click Here");
    ASSERT_EQ(obj["widget"]["text"]["size"].AsDouble(), 36.0);
    ASSERT_EQ(obj["widget"]["text"]["style"].AsString(), "bold");
    ASSERT_EQ(obj["widget"]["text"]["name"].AsString(), "text1");
    ASSERT_EQ(obj["widget"]["text"]["hOffset"].AsDouble(), 250.0);
    ASSERT_EQ(obj["widget"]["text"]["vOffset"].AsDouble(), 100.0);
    ASSERT_EQ(obj["widget"]["text"]["alignment"].AsString(), "center");
    ASSERT_EQ(obj["widget"]["text"]["onMouseUp"].AsString(), "sun1.opacity = (sun1.opacity / 100) * 90;");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}