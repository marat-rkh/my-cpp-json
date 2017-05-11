#ifndef __JSON_MODEL_H__
#define __JSON_MODEL_H__

#include <string>
#include <map>
#include <vector>
#include <initializer_list>

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

class JTypeUtils {
public:
    static std::string ToString(JType const &t);
};

namespace inner { namespace json_model {

class JsonValue {
public:
    virtual JType type() const = 0;
    virtual ~JsonValue() {}
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
    using iterator = std::map<std::string, Json>::iterator;
    using const_iterator = std::map<std::string, Json>::const_iterator;
    
    JsonObject() = default;
    explicit JsonObject(std::initializer_list<std::pair<const std::string, Json>> const &lst);

    JType type() const override { return JType::JOBJECT; }
    // TODO change to custom map that keeps insertion order
    // (e.g. as a vector of string*)
    std::map<std::string, Json> &value() { return value_; }
private:
    std::map<std::string, Json> value_;
};

class JsonArray: public JsonValue {
public:
    using size_type = std::vector<Json>::size_type;
    using iterator = std::vector<Json>::iterator;
    using const_iterator = std::vector<Json>::const_iterator;

    JsonArray() = default;
    explicit JsonArray(std::initializer_list<Json> const &lst);

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

}

#endif