#ifndef __JSON_REF_H__
#define __JSON_REF_H__

#include <memory>
#include <string>

#include "json_model.h"
#include "json_accessors.h"

namespace json_cpp {

class Json;

class JsonRef {
    friend class Json;
public:
    using size_type = JsonAccessors::size_type;

    JsonRef(std::shared_ptr<inner::json_model::JsonValue>& value_ref);
    JsonRef &operator=(Json const &json);
    JsonRef &operator=(Json &&json);

    JsonRef(JsonRef const &r) = default;
    JsonRef &operator=(JsonRef const &r) = default;
    // These two make copy as JsonRef is a proxy for reference 
    // and there is no meaning of moving reference
    JsonRef(JsonRef &&r);
    JsonRef &operator=(JsonRef &&r);

    std::string const &AsString() const;
    double AsDouble() const;
    bool AsBool() const;
    std::nullptr_t AsNull() const;

    JType Type() const { return value_ref_ ? value_ref_->type() : JType::JNULL; }

    JsonRef const operator[](std::string const &field_name) const;
    JsonRef operator[](std::string const &field_name);

    JsonRef const operator[](size_type index) const;
    JsonRef operator[](size_type index);
private:
    std::shared_ptr<inner::json_model::JsonValue> &value_ref_;
};

}

#endif