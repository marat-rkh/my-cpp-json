#ifndef __JSON_H__
#define __JSON_H__

#include <string>
#include <memory>
#include <map>
#include <vector>
#include <cstddef>
#include <initializer_list>

#include "json_model.h"
#include "utils.h"

namespace json_cpp {

class Json {
public:
    using size_type = inner::json_model::JsonArray::size_type;
    using object_iterator = inner::json_model::JsonObject::iterator;
    using object_const_iterator = inner::json_model::JsonObject::const_iterator;
    using array_iterator = inner::json_model::JsonArray::iterator;
    using array_const_iterator = inner::json_model::JsonArray::const_iterator;

    Json() = default;
    Json(std::nullptr_t np): Json() {}
    Json(std::string const& str);
    Json(char const *c_str): Json(std::string(c_str)) {}
    Json(double num);
    Json(int num): Json(static_cast<double>(num)) {}
    Json(bool b);
    Json(std::initializer_list<std::pair<const std::string, Json>> const &lst);

    Json const &operator[](std::string const &field_name) const;
    Json &operator[](std::string const &field_name);

    Json const &operator[](size_type index) const;
    Json &operator[](size_type index);

    Json &operator+=(Json const& val);

    Json &operator=(Json const& other);

    object_iterator ObjectBegin();
    object_const_iterator ObjectBegin() const;
    object_iterator ObjectEnd();
    object_const_iterator ObjectEnd() const;
    array_iterator ArrayBegin();
    array_const_iterator ArrayBegin() const;
    array_iterator ArrayEnd();
    array_const_iterator ArrayEnd() const;

    std::string const &AsString() const;
    double AsDouble() const;
    bool AsBool() const;
    std::nullptr_t AsNull() const;

    JType Type() const { return value_ ? value_->type() : JType::JNULL; }

    // these functions are meant to be used as literals 
    // so they have short lower case names
    static Json obj(std::initializer_list<std::pair<const std::string, Json>> const &lst = {});
    static Json arr(std::initializer_list<Json> const &lst = {});
private:
    std::shared_ptr<inner::json_model::JsonValue> value_;
};

}

#endif