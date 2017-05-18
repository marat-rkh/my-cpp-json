#ifndef __JSON_BASIC_H__
#define __JSON_BASIC_H__

#include <memory>
#include "json_model.h"

namespace json_cpp {

// TODO prohibit pointers creation
class JsonBasic {
public:
    std::string const &AsString() const;
    double AsDouble() const;
    bool AsBool() const;
    std::nullptr_t AsNull() const;

    JType Type() const { 
        auto &val = Value();
        return val ? val->type() : JType::JNULL; 
    }
protected:
    virtual std::shared_ptr<inner::json_model::JsonValue> &Value() = 0;
    virtual std::shared_ptr<inner::json_model::JsonValue> const &Value() const = 0;
};

}

#endif