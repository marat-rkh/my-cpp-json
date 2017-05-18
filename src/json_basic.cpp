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
