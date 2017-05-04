#include "json.h"

#include <stdexcept>

using namespace json_cpp;
using namespace json_cpp::inner::json_model;

using std::string;
using std::make_shared;
using std::pair;
using std::runtime_error;
using std::initializer_list;

Json::Json(std::string const& str)
    : value_(make_shared<JsonString>(str))
{}

Json::Json(double num)
    : value_(make_shared<JsonNumber>(num))
{}

Json::Json(bool b)
    : value_(make_shared<JsonBool>(b))
{}

Json::Json(std::initializer_list<std::pair<const std::string, Json>> const &lst)
    : value_(make_shared<JsonObject>(lst))
{}

Json const &Json::operator[](string const &field_name) const {
    if(value_->type() == JType::JOBJECT) {
        return as<JsonObject>(value_)->value()[field_name];
    } else {
        throw runtime_error("attempt to access field on non object json value");
    }
}

Json &Json::operator[](string const &field_name) {
    Json const *cthis = this;
    Json const &cres = (*cthis)[field_name];
    return const_cast<Json &>(cres);
}

Json const &Json::operator[](size_type index) const {
    if(value_->type() == JType::JARRAY) {
        return as<JsonArray>(value_)->value()[index];
    } else {
        throw runtime_error("attempt to index non array json value");
    }
}

Json &Json::operator[](size_type index) {
    Json const *cthis = this;
    Json const &cres = (*cthis)[index];
    return const_cast<Json &>(cres);
}

Json &Json::operator+=(Json const& val) {
    if(value_->type() == JType::JARRAY) {
        as<JsonArray>(value_)->value().push_back(val);
        return *this;
    } else {
        throw runtime_error("attempt to element to non array json value");
    }
}

Json &Json::operator=(Json const& other) {
    if(this != &other) {
        value_ = other.value_;
    }
    return *this;
}

string const &Json::AsString() const {
    if(!value_ || value_->type() != JType::JSTRING) {
        throw runtime_error("attempt to convert non string json value to string");
    }
    return as<JsonString>(value_)->value();
}

double Json::AsDouble() const {
    if(!value_ || value_->type() != JType::JNUMBER) {
        throw runtime_error("attempt to convert non numeric json value to double");
    }
    return as<JsonNumber>(value_)->value();
}

bool Json::AsBool() const {
    if(!value_ || value_->type() != JType::JBOOL) {
        throw runtime_error("attempt to convert non bool json value to bool");
    }
    return as<JsonBool>(value_)->value();
}

std::nullptr_t Json::AsNull() const {
    if(value_) {
        throw runtime_error("attempt to convert non null json value to nullptr");
    }
    return nullptr;
}

// static members

Json Json::obj(initializer_list<pair<const string, Json>> const &lst) {
    return Json(lst);
}

Json Json::arr(initializer_list<Json> const &lst) {
    Json arr;
    arr.value_ = make_shared<JsonArray>(lst);
    return arr;
}