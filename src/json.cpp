#include "json.h"

#include <stdexcept>

#include "json_ref.h"
#include "const_json_ref.h"

using namespace json_cpp;
using namespace json_cpp::inner::json_model;
using namespace json_cpp::inner::utils;

using std::string;
using std::pair;
using std::runtime_error;
using std::initializer_list;
using std::make_shared;
using std::shared_ptr;

Json::Json(string const& str)
    : value_(new JsonString(str))
{}

Json::Json(double num)
    : value_(new JsonNumber(num))
{}

Json::Json(bool b)
    : value_(new JsonBool(b))
{}

Json::Json(initializer_list<pair<const string, Json>> const &lst) {
    auto obj = make_shared<JsonObject>();
    auto &map = obj->value();
    for(auto &p: lst) {
        map.insert(p.first, p.second.value_);
    }
    value_ = std::move(obj);
}

Json::Json(JsonRef const &json_ref)
    : value_(CopyJsonTree(json_ref.value_ref_))
{}

Json::Json(Json const &other) 
    : value_(CopyJsonTree(other.value_))
{}

Json::Json(Json &&other) noexcept
    : value_(std::move(other.value_))
{}

Json::~Json() {}

Json &Json::operator=(Json const& other) {
    if(this != &other) {
        value_ = CopyJsonTree(other.value_);
    }
    return *this;
}

Json &Json::operator=(Json &&other) noexcept {
    if(this != &other) {
        value_ = std::move(other.value_);
    }
    return *this;
}

Json &Json::operator+=(Json const& elem) {
    AddElemToArray(elem);
    return *this;
}
Json &Json::operator+=(JsonRef const& elem) {
    AddElemToArray(elem);
    return *this;
}
Json &Json::operator+=(ConstJsonRef const& elem) {
    AddElemToArray(elem);
    return *this;
}

// static members

Json Json::obj(initializer_list<pair<const string, Json>> const &lst) {
    return Json(lst);
}

Json Json::arr(initializer_list<Json> const &lst) {
    auto arr = make_shared<JsonArray>();
    auto &vec = arr->value();
    for(auto &l: lst) {
        vec.push_back(l.value_);
    }
    Json json;
    json.value_ = std::move(arr);
    return json;
}