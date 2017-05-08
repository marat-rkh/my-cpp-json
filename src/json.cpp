#include "json.h"

#include <stdexcept>

using namespace json_cpp;
using namespace json_cpp::inner::json_model;

using std::string;
using std::pair;
using std::runtime_error;
using std::initializer_list;

Json::Json(string const& str)
    : value_(new JsonString(str))
{}

Json::Json(double num)
    : value_(new JsonNumber(num))
{}

Json::Json(bool b)
    : value_(new JsonBool(b))
{}

Json::Json(initializer_list<pair<const string, Json>> const &lst)
    : value_(new JsonObject(lst))
{}

Json::Json(Json const &other) {
    CopyValue(other);
}

Json::Json(Json &&other) noexcept
    : value_(std::move(other.value_))
{}

Json::~Json() {}

Json &Json::operator=(Json const& other) {
    if(this != &other) {
        CopyValue(other);
    }
    return *this;
}

Json &Json::operator=(Json &&other) noexcept {
    if(this != &other) {
        value_ = std::move(other.value_);
    }
    return *this;
}

inline string InvalidOperation(string const &prefix, JType const &t) {
    return prefix + JTypeUtils::ToString(t);
}

Json const &Json::operator[](string const &field_name) const {
    if(value_->type() == JType::JOBJECT) {
        return as<JsonObject>(value_)->value()[field_name];
    }
    throw runtime_error(InvalidOperation("attempt to access field on ", value_->type()));
}

Json &Json::operator[](string const &field_name) {
    Json const *cthis = this;
    Json const &cres = (*cthis)[field_name];
    return const_cast<Json &>(cres);
}

Json const &Json::operator[](size_type index) const {
    if(value_->type() == JType::JARRAY) {
        return as<JsonArray>(value_)->value()[index];
    }
    throw runtime_error(InvalidOperation("attempt to index ", value_->type()));
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
    }
    throw runtime_error(InvalidOperation("attempt to append element to ", value_->type()));
}

Json::object_iterator Json::ObjectBegin() {
    if(value_->type() == JType::JOBJECT) {
        return as<JsonObject>(value_)->value().begin();
    }
    throw runtime_error(InvalidOperation("attempt to access object iterator on ", value_->type()));
}

Json::object_const_iterator Json::ObjectBegin() const {
    if(value_->type() == JType::JOBJECT) {
        return as<JsonObject>(value_)->value().begin();
    }
    throw runtime_error(InvalidOperation("attempt to access object iterator on ", value_->type()));
}

Json::object_iterator Json::ObjectEnd() {
    if(value_->type() == JType::JOBJECT) {
        return as<JsonObject>(value_)->value().end();
    }
    throw runtime_error(InvalidOperation("attempt to access object iterator on ", value_->type()));
}

Json::object_const_iterator Json::ObjectEnd() const {
    if(value_->type() == JType::JOBJECT) {
        return as<JsonObject>(value_)->value().end();
    }
    throw runtime_error(InvalidOperation("attempt to access object iterator on ", value_->type()));
}

Json::array_iterator Json::ArrayBegin() {
    if(value_->type() == JType::JARRAY) {
        return as<JsonArray>(value_)->value().begin();
    }
    throw runtime_error(InvalidOperation("attempt to access array iterator on ", value_->type()));
}

Json::array_const_iterator Json::ArrayBegin() const {
    if(value_->type() == JType::JARRAY) {
        return as<JsonArray>(value_)->value().begin();
    }
    throw runtime_error(InvalidOperation("attempt to access array iterator on ", value_->type()));
}

Json::array_iterator Json::ArrayEnd() {
    if(value_->type() == JType::JARRAY) {
        return as<JsonArray>(value_)->value().end();
    }
    throw runtime_error(InvalidOperation("attempt to access array iterator on ", value_->type()));
}

Json::array_const_iterator Json::ArrayEnd() const {
    if(value_->type() == JType::JARRAY) {
        return as<JsonArray>(value_)->value().end();
    }
    throw runtime_error(InvalidOperation("attempt to access array iterator on ", value_->type()));
}

inline string BadConversion(JType const &from, string const &to) {
    string msg = "attempt to convert ";
    return msg + JTypeUtils::ToString(from) + " to " + to;
}

string const &Json::AsString() const {
    if(!value_ || value_->type() != JType::JSTRING) {
        throw runtime_error(BadConversion(value_->type(), "string"));
    }
    return as<JsonString>(value_)->value();
}

double Json::AsDouble() const {
    if(!value_ || value_->type() != JType::JNUMBER) {
        throw runtime_error(BadConversion(value_->type(), "double"));
    }
    return as<JsonNumber>(value_)->value();
}

bool Json::AsBool() const {
    if(!value_ || value_->type() != JType::JBOOL) {
        throw runtime_error(BadConversion(value_->type(), "bool"));
    }
    return as<JsonBool>(value_)->value();
}

nullptr_t Json::AsNull() const {
    if(value_) {
        throw runtime_error(BadConversion(value_->type(), "nullptr"));
    }
    return nullptr;
}

// static members

Json Json::obj(initializer_list<pair<const string, Json>> const &lst) {
    return Json(lst);
}

Json Json::arr(initializer_list<Json> const &lst) {
    Json arr;
    arr.value_.reset(new JsonArray(lst));
    return arr;
}

// private members

void Json::CopyValue(Json const &json) {
    switch(json.Type()) {
        case JType::JSTRING: CopyAs<JsonString>(json); break;
        case JType::JNUMBER: CopyAs<JsonNumber>(json); break;
        case JType::JOBJECT: CopyAs<JsonObject>(json); break;
        case JType::JARRAY: CopyAs<JsonArray>(json); break;
        case JType::JBOOL: CopyAs<JsonBool>(json); break;
        case JType::JNULL: break;
        default:
            throw std::runtime_error("unexcepted JType enum value");
    }
}