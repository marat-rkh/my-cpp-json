#include "gtest/gtest.h"
 
#include "json_value.h"

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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}