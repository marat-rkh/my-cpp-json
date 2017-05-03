#ifndef __JSON_H__
#define __JSON_H__

#include <string>
#include <memory>
#include <map>
#include <vector>
#include <cstddef>

#include "json_model.h"
#include "utils.h"

namespace json_cpp {

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

    // TODO replace with one operator accepting Json const & (implicit conversions will do the rest)
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