#ifndef __JSON_VALUE_H__
#define __JSON_VALUE_H__

#include <string>
#include <memory>
#include <map>
#include <vector>

#include "utils.h"

namespace json_cpp {

class JsonValue {
public:
    enum class Type {
        JSTRING,
        JNUMBER,
        JOBJECT,
        JARRAY,
        JBOOL,
        JNULL
    };
    virtual Type type() const = 0;
};

class JsonString: public JsonValue {
public:
    explicit JsonString(std::string const &s): value_(s) {}

    Type type() const override { return Type::JSTRING; }

    std::string const &value() const { return value_; }
    void value(const std::string &v) { value_ = v; }
private:
    std::string value_;
};

class JsonNumber: public JsonValue {
public:
    explicit JsonNumber(double v): value_(v) {}

    Type type() const override { return Type::JNUMBER; }
    
    double value() const { return value_; }
    void value(double v) { value_ = v; }
private:
    double value_ = 0.0;
};

class JsonObject: public JsonValue {
public:
    explicit JsonObject(std::map<std::string, std::shared_ptr<JsonValue>> const &vs)
        : values_(vs)
    {}

    Type type() const override { return Type::JOBJECT; }

    JsonValue const &get(std::string const &key) const { return *(values_.at(key)); }
    void set(
        std::string const &key, 
        std::shared_ptr<JsonValue> const &val
    ) { values_[key] = val; }
private:
    std::map<std::string, std::shared_ptr<JsonValue>> values_;
};

class JsonArray: public JsonValue {
public:
    using size_type = std::vector<JsonValue>::size_type;

    Type type() const override { return Type::JARRAY; }

    JsonValue const &get(size_type pos) const { return *(values_[pos]); }
    void set(size_type pos, std::shared_ptr<JsonValue> const &val) { values_[pos] = val; }
private:
    std::vector<std::shared_ptr<JsonValue>> values_;
};

class JsonBool: public JsonValue {
public:
    explicit JsonBool(bool b): value_(b) {}

    Type type() const override { return Type::JBOOL; }

    bool value() const { return value_; }
    void value(bool v) { value_ = v; }
private:
    bool value_ = false;
};

class JsonNull: public JsonValue {
public:
    Type type() const override { return Type::JNULL; }

    static std::shared_ptr<JsonNull> const &GetPtr() {
        static auto instance = std::shared_ptr<JsonNull>(new JsonNull());
        return instance;
    }

    static JsonNull &Get() {
        return *GetPtr();
    }
private:
    JsonNull() {}
public:
    JsonNull(JsonNull const &) = delete;
    void operator=(JsonNull const &) = delete;
};

}

#endif