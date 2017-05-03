#include "gtest/gtest.h"
 
#include "json.h"

using json_cpp::Json;
using json_cpp::JType;

TEST(json, should_handle_string) {
    Json json("some str");
    ASSERT_EQ(json.Type(), JType::JSTRING);
    ASSERT_EQ(json.AsString(), "some str");
}

TEST(json, should_handle_number) {
    Json json(123.0);
    ASSERT_EQ(json.Type(), JType::JNUMBER);
    ASSERT_EQ(json.AsDouble(), 123.0);
}

TEST(json, should_handle_bool) {
    Json json(true);
    ASSERT_EQ(json.Type(), JType::JBOOL);
    ASSERT_EQ(json.AsBool(), true);
}

TEST(json, should_handle_null) {
    Json json1;
    ASSERT_EQ(json1.Type(), JType::JNULL);
    ASSERT_EQ(json1.AsNull(), nullptr);
    Json json2(nullptr);
    ASSERT_EQ(json2.Type(), JType::JNULL);
    ASSERT_EQ(json2.AsNull(), nullptr);
}

TEST(json, should_handle_array) {
    Json json;
    json += "some str";
    json += "other str";
    json += 123.0;
    json += false;
    json += nullptr;
    ASSERT_EQ(json.Type(), JType::JARRAY);
    ASSERT_EQ(json[0].AsString(), "some str");
    ASSERT_EQ(json[1].AsString(), "other str");
    ASSERT_EQ(json[2].AsDouble(), 123.0);
    ASSERT_EQ(json[3].AsBool(), false);
    ASSERT_EQ(json[4].AsNull(), nullptr);

    ASSERT_EQ(Json::MakeArray().Type(), JType::JARRAY);
}

TEST(json, should_handle_object) {
    Json json;
    json += {"field1", "some str"};
    json += {"field2", 123.0};
    Json sub_obj;
    sub_obj += {"sub field", true};
    json += {"field3", sub_obj};
    ASSERT_EQ(json.Type(), JType::JOBJECT);
    ASSERT_EQ(json["field1"].AsString(), "some str");
    ASSERT_EQ(json["field2"].AsDouble(), 123.0);
    ASSERT_EQ(json["field3"]["sub field"].AsBool(), true);
    ASSERT_EQ(json["no such field"].AsNull(), nullptr);

    ASSERT_EQ(Json::MakeObject().Type(), JType::JOBJECT);
}

TEST(json, should_handle_assignment) {
    Json json;
    ASSERT_EQ(json.Type(), JType::JNULL);
    json = "string";
    ASSERT_EQ(json.Type(), JType::JSTRING);
    json = 123.0;
    ASSERT_EQ(json.Type(), JType::JNUMBER);
    json = std::string("string");
    ASSERT_EQ(json.Type(), JType::JSTRING);
    json = false;
    ASSERT_EQ(json.Type(), JType::JBOOL);
}

TEST(json, should_handle_real_world1_json) {
    Json gloss_see_also;
    gloss_see_also += "GML";
    gloss_see_also += "XML";
    Json gloss_def;
    gloss_def += {"para", "A meta-markup language, used to create markup languages such as DocBook."};
    gloss_def += {"GlossSeeAlso", gloss_see_also};
    Json gloss_entry;
    gloss_entry += {"ID", "SGML"};
    gloss_entry += {"SortAs", "SGML"};
    gloss_entry += {"GlossTerm", "Standard Generalized Markup Language"};
    gloss_entry += {"Acronym", "SGML"};
    gloss_entry += {"Abbrev", "ISO 8879:1986"};
    gloss_entry += {"GlossDef", gloss_def};
    gloss_entry += {"GlossSee", "markup"};
    Json gloss_list;
    gloss_list += {"GlossEntry", gloss_entry};
    Json gloss_div;
    gloss_div += {"title", "S"};
    gloss_div += {"GlossList", gloss_list};
    Json glossary;
    glossary += {"title", "example glossary"};
    glossary += {"GlossDiv", gloss_div};
    Json obj;
    obj += {"glossary", glossary};

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

TEST(json, should_handle_real_world2_json) {
    Json window;
    window += {"title", "Sample Konfabulator Widget"};
    window += {"name", "main_window"};
    window += {"width", 500.0};
    window += {"height", 500.0};
    Json image;
    image += {"src", "Images/Sun.png"};
    image += {"name", "sun1"};
    image += {"hOffset", 250.0};
    image += {"vOffset", 250.0};
    image += {"alignment", "center"};
    Json text;
    text += {"data", "Click Here"};
    text += {"size", 36.0};
    text += {"style", "bold"};
    text += {"name", "text1"};
    text += {"hOffset", 250.0};
    text += {"vOffset", 100.0};
    text += {"alignment", "center"};
    text += {"onMouseUp", "sun1.opacity = (sun1.opacity / 100) * 90;"};
    Json widget;
    widget += {"debug", "on"};
    widget += {"window", window};
    widget += {"image", image};
    widget += {"text", text};
    Json obj;
    obj += {"widget", widget};

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