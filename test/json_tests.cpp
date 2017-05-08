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

    Json json2(123);
    ASSERT_EQ(json2.Type(), JType::JNUMBER);
    ASSERT_EQ(json2.AsDouble(), 123);
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
    Json json = Json::arr({"some str", "other str", 123.0, false, nullptr});
    ASSERT_EQ(json.Type(), JType::JARRAY);
    ASSERT_EQ(json[0].AsString(), "some str");
    ASSERT_EQ(json[1].AsString(), "other str");
    ASSERT_EQ(json[2].AsDouble(), 123.0);
    ASSERT_EQ(json[3].AsBool(), false);
    ASSERT_EQ(json[4].AsNull(), nullptr);

    json += 1;
    json += "abs";
    json += false;
    ASSERT_EQ(json[5].AsDouble(), 1.0);
    ASSERT_EQ(json[6].AsString(), "abs");
    ASSERT_EQ(json[7].AsBool(), false);
    
    json[7] = {{"a", 1}, {"b", 2}};
    ASSERT_EQ(json[7]["a"].AsDouble(), 1);
    ASSERT_EQ(json[7]["b"].AsDouble(), 2);
}

TEST(json, should_handle_object) {
    Json json{
        {"field1", "some str"},
        {"field2", 123.0},
        {"field3", {
            {"sub field", true}
        }},
        {"field4", Json::arr({false, false, true})}
    };
    ASSERT_EQ(json.Type(), JType::JOBJECT);
    ASSERT_EQ(json["field1"].AsString(), "some str");
    ASSERT_EQ(json["field2"].AsDouble(), 123.0);
    ASSERT_EQ(json["field3"]["sub field"].AsBool(), true);
    ASSERT_EQ(json["field4"].Type(), JType::JARRAY);
    ASSERT_EQ(json["no such field"].AsNull(), nullptr);
    json["field5"] = "other str";
    ASSERT_EQ(json["field5"].AsString(), "other str");

    ASSERT_EQ(Json::obj().Type(), JType::JOBJECT);
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
    json = Json::obj();
    ASSERT_EQ(json.Type(), JType::JOBJECT);
}

TEST(json, should_handle_real_world1_json) {
    Json obj{
        {"glossary", {
            {"title","example glossary"},
            {"GlossDiv", {
                {"title", "S"},
                {"GlossList", {
                    {"GlossEntry", {
                        {"ID", "SGML"},
                        {"SortAs","SGML"},
                        {"GlossTerm","Standard Generalized Markup Language"},
                        {"Acronym","SGML"},
                        {"Abbrev","ISO 8879:1986"},
                        {"GlossDef", {
                            {"para", "A meta-markup language, used to create markup languages such as DocBook."},
                            {"GlossSeeAlso", Json::arr({"GML", "XML"})}
                        }},
                        {"GlossSee","markup"}
                    }}
                }}
            }}
        }}
    };

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
    Json obj{
        {"widget", {
            {"debug", "on"},
            {"window", {
                {"title", "Sample Konfabulator Widget"},
                {"name", "main_window"},
                {"width", 500},
                {"height", 500}
            }},
            {"image", {
                {"src", "Images/Sun.png"},
                {"name", "sun1"},
                {"hOffset", 250},
                {"vOffset", 250},
                {"alignment", "center"}
            }},
            {"text", {
                {"data", "Click Here"},
                {"size", 36},
                {"style", "bold"},
                {"name", "text1"},
                {"hOffset", 250},
                {"vOffset", 100},
                {"alignment", "center"},
                {"onMouseUp", "sun1.opacity = (sun1.opacity / 100) * 90;"}
            }}
        }}
    };

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

TEST(json, should_be_copied) {
    Json json {
        {"a", 1},
        {"b", {
            {"c", 2}
        }}
    };
    Json copy1(json);
    copy1["a"] = 3;
    ASSERT_EQ(json["a"].AsDouble(), 1);
    ASSERT_EQ(json["b"]["c"].AsDouble(), 2);
    ASSERT_EQ(copy1["a"].AsDouble(), 3);
    ASSERT_EQ(copy1["b"]["c"].AsDouble(), 2);
    Json copy2;
    copy2 = json;
    copy2["b"]["c"] = 4;
    ASSERT_EQ(json["a"].AsDouble(), 1);
    ASSERT_EQ(json["b"]["c"].AsDouble(), 2);
    ASSERT_EQ(copy2["a"].AsDouble(), 1);
    ASSERT_EQ(copy2["b"]["c"].AsDouble(), 4);
}

TEST(json, should_be_moved) {
    Json json {
        {"a", 1},
        {"b", {
            {"c", 2}
        }}
    };
    Json moved1(std::move(json));
    moved1["a"] = 3;
    ASSERT_EQ(json.Type(), JType::JNULL);
    ASSERT_EQ(moved1["a"].AsDouble(), 3);
    ASSERT_EQ(moved1["b"]["c"].AsDouble(), 2);
    Json moved2;
    moved2 = std::move(moved1);
    moved2["b"]["c"] = 4;
    ASSERT_EQ(moved1.Type(), JType::JNULL);
    ASSERT_EQ(moved2["a"].AsDouble(), 3);
    ASSERT_EQ(moved2["b"]["c"].AsDouble(), 4);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}