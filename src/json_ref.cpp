#include "json_ref.h"

#include "json.h"
#include "utils.h"

#include <stdexcept>

using std::shared_ptr;
using std::string;
using std::runtime_error;
using std::nullptr_t;

using namespace json_cpp;
using namespace json_cpp::inner::json_model;

JsonRef::JsonRef(shared_ptr<JsonValue>& value_ref)
    : value_ref_(value_ref)
{}

JsonRef &JsonRef::operator=(Json const &json) {
    if(value_ref_ != json.value_) {
        value_ref_ = CopyJsonTree(json.value_);
    }
    return *this;
}

JsonRef &JsonRef::operator=(Json &&json) {
    if(value_ref_ != json.value_) {
        value_ref_ = json.value_;
    }
    return *this;
}

JsonRef::JsonRef(JsonRef &&r)
    : value_ref_(r.value_ref_)
{}

JsonRef &JsonRef::operator=(JsonRef &&r) {
    if(this != &r) {
        value_ref_ = r.value_ref_;
    }
    return *this;
}

// TODO all these methods duplicate code in json.cpp
inline string BadConversion(JType const &from, string const &to) {
    string msg = "attempt to convert ";
    return msg + JTypeUtils::ToString(from) + " to " + to;
}

string const &JsonRef::AsString() const {
    if(!value_ref_ || value_ref_->type() != JType::JSTRING) {
        throw runtime_error(BadConversion(value_ref_->type(), "string"));
    }
    return as<JsonString>(value_ref_)->value();
}

double JsonRef::AsDouble() const {
    if(!value_ref_ || value_ref_->type() != JType::JNUMBER) {
        throw runtime_error(BadConversion(value_ref_->type(), "double"));
    }
    return as<JsonNumber>(value_ref_)->value();
}

bool JsonRef::AsBool() const {
    if(!value_ref_ || value_ref_->type() != JType::JBOOL) {
        throw runtime_error(BadConversion(value_ref_->type(), "bool"));
    }
    return as<JsonBool>(value_ref_)->value();
}

nullptr_t JsonRef::AsNull() const {
    if(value_ref_) {
        throw runtime_error(BadConversion(value_ref_->type(), "nullptr"));
    }
    return nullptr;
}

JsonRef const JsonRef::operator[](string const &field_name) const {
    return JsonAccessors::AccessField(value_ref_, field_name);
}

JsonRef JsonRef::operator[](string const &field_name) {
    return JsonAccessors::AccessField(value_ref_, field_name);
}

JsonRef const JsonRef::operator[](size_type index) const {
    return JsonAccessors::AccessElem(value_ref_, index);
}

JsonRef JsonRef::operator[](size_type index) {
    return JsonAccessors::AccessElem(value_ref_, index);
}