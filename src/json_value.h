#ifndef __JSON_VALUE_H__
#define __JSON_VALUE_H__

#include <string>
#include <memory>
#include <map>
#include <vector>
#include <cstddef>

#include "utils.h"

namespace json_cpp {

class Json;

enum class JType {
    JSTRING,
    JNUMBER,
    JOBJECT,
    JARRAY,
    JBOOL,
    JNULL
};

// TODO move to separate file
namespace inner { namespace json_model {

class JsonValue {
public:
    virtual JType type() const = 0;
};

class JsonString: public JsonValue {
public:
    explicit JsonString(std::string const &s): value_(s) {}

    JType type() const override { return JType::JSTRING; }
    std::string &value() { return value_; }
private:
    std::string value_;
};

class JsonNumber: public JsonValue {
public:
    explicit JsonNumber(double v): value_(v) {}

    JType type() const override { return JType::JNUMBER; }
    double &value() { return value_; }
private:
    double value_ = 0.0;
};

class JsonObject: public JsonValue {
public:
    JType type() const override { return JType::JOBJECT; }
    std::map<std::string, Json> &value() { return value_; }
private:
    std::map<std::string, Json> value_;
};

class JsonArray: public JsonValue {
public:
    using size_type = std::vector<JsonValue>::size_type;

    JType type() const override { return JType::JARRAY; }
    std::vector<Json> &value() { return value_; }
private:
    std::vector<Json> value_;
};

class JsonBool: public JsonValue {
public:
    explicit JsonBool(bool b): value_(b) {}

    JType type() const override { return JType::JBOOL; }
    bool &value() { return value_; }
private:
    bool value_ = false;
};

}} // namespace inner::json_model

class Json {
public:
    using size_type = inner::json_model::JsonArray::size_type;

    Json() = default;
    Json(std::nullptr_t np): Json() {}
    Json(std::string const& str);
    Json(char const *c_str): Json(std::string(c_str)) {}
    Json(double num);
    Json(bool b);

    Json const &operator[](std::string const &field_name) const;
    Json &operator[](std::string const &field_name);

    Json const &operator[](size_type index) const;
    Json &operator[](size_type index);

    Json &operator+=(std::pair<std::string, Json> const& pair);
    Json &operator+=(Json const& val);

    Json &operator=(std::string const& str);
    Json &operator=(char const *c_str) { return (*this) = std::string(c_str); }
    Json &operator=(double num);
    Json &operator=(bool b);
    Json &operator=(std::nullptr_t np);

    std::string const &AsString() const;
    double AsDouble() const;
    bool AsBool() const;
    std::nullptr_t AsNull() const;

    JType Type() { return value_ ? value_->type() : JType::JNULL; }

    static Json MakeObject();
    static Json MakeArray();
private:
    std::shared_ptr<inner::json_model::JsonValue> value_;
};

}

#endif