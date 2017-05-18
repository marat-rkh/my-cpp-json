#include "json_basic.h"

#include <string>
#include <stdexcept>
#include <utility>

#include "utils.h"
#include "const_json_ref.h"

using namespace json_cpp;
using namespace json_cpp::inner::json_model;
using namespace json_cpp::inner::utils;

using std::string;
using std::nullptr_t;
using std::runtime_error;
using std::pair;
using std::make_pair;

inline string BadConversion(JType const &from, string const &to) {
    string msg = "attempt to convert ";
    return msg + JTypeUtils::ToString(from) + " to " + to;
}

string const &JsonBasic::AsString() const {
    // TODO this pattern is common for most methods in JsonBasic
    // hierarchy. Extract it to method accepting lambda
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

ConstJsonRef JsonBasic::operator[](std::string const &field_name) const {
    return ConstJsonRef(AccessField(field_name));
}
    
ConstJsonRef JsonBasic::operator[](ArraySizeType index) const {
    return ConstJsonRef(AccessElem(index));
}

inline string InvalidOperation(string const &prefix, JType const &t) {
    return prefix + JTypeUtils::ToString(t);
}

JsonBasic::ObjectConstIterator JsonBasic::ObjectBegin() const {
    auto &val = Value();
    if(val->type() == JType::JOBJECT) {
        return MakeMappingBegin(as<JsonObject>(val)->value().begin(), &JsonBasic::ProxyPair<ConstJsonRef>);
    }
    throw runtime_error(InvalidOperation("attempt to access object iterator on ", val->type()));
}

JsonBasic::ObjectConstIterator JsonBasic::ObjectEnd() const {
    auto &val = Value();
    if(val->type() == JType::JOBJECT) {
        return MakeMappingEnd(as<JsonObject>(val)->value().end(), &JsonBasic::ProxyPair<ConstJsonRef>);
    }
    throw runtime_error(InvalidOperation("attempt to access object iterator on ", val->type()));
}

JsonBasic::ArrayConstIterator JsonBasic::ArrayBegin() const {
    auto &val = Value();
    if(val->type() == JType::JARRAY) {
        return MakeMappingBegin(as<JsonArray>(val)->value().begin(), &JsonBasic::ProxyElem<ConstJsonRef>);
    }
    throw runtime_error(InvalidOperation("attempt to access array iterator on ", val->type()));
}

JsonBasic::ArrayConstIterator JsonBasic::ArrayEnd() const {
    auto &val = Value();
    if(val->type() == JType::JARRAY) {
        return MakeMappingEnd(as<JsonArray>(val)->value().end(), &JsonBasic::ProxyElem<ConstJsonRef>);
    }
    throw runtime_error(InvalidOperation("attempt to access array iterator on ", val->type()));
}

// protected

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