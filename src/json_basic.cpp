#include "json_basic.h"

#include <string>
#include <stdexcept>

#include "utils.h"

using namespace json_cpp;
using namespace json_cpp::inner::json_model;

using std::string;
using std::nullptr_t;
using std::runtime_error;

inline string BadConversion(JType const &from, string const &to) {
    string msg = "attempt to convert ";
    return msg + JTypeUtils::ToString(from) + " to " + to;
}

string const &JsonBasic::AsString() const {
    auto &val = Value();
    if(!val || val->type() != JType::JSTRING) {
        throw runtime_error(BadConversion(val->type(), "string"));
    }
    return as<JsonString>(val)->value();
}

double JsonBasic::AsDouble() const {
    auto &val = Value();
    if(!val || val->type() != JType::JNUMBER) {
        throw runtime_error(BadConversion(val->type(), "double"));
    }
    return as<JsonNumber>(val)->value();
}

bool JsonBasic::AsBool() const {
    auto &val = Value();
    if(!val || val->type() != JType::JBOOL) {
        throw runtime_error(BadConversion(val->type(), "bool"));
    }
    return as<JsonBool>(val)->value();
}

nullptr_t JsonBasic::AsNull() const {
    auto &val = Value();
    if(val) {
        throw runtime_error(BadConversion(val->type(), "nullptr"));
    }
    return nullptr;
}

inline string InvalidOperation(string const &prefix, JType const &t) {
    return prefix + JTypeUtils::ToString(t);
}

JsonBasic::JsonValuePtr const &JsonBasic::AccessField(string const &field_name) const {
    auto &value = Value();
    if(value->type() == JType::JOBJECT) {
        return as<JsonObject>(value)->value()[field_name];
    }
    throw runtime_error(InvalidOperation("attempt to access field on ", value->type()));
}

JsonBasic::JsonValuePtr const &JsonBasic::AccessElem(ArraySizeType index) const {
    auto &value = Value();
    if(value->type() == JType::JARRAY) {
        return as<JsonArray>(value)->value()[index];
    }
    throw runtime_error(InvalidOperation("attempt to index ", value->type()));
}