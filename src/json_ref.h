#ifndef __JSON_REF_H__
#define __JSON_REF_H__

#include <memory>
#include <string>

#include "json_model.h"
#include "json_mutable.h"

namespace json_cpp {

class Json;
class ConstJsonRef;

class JsonRef: public JsonMutable {
    friend class JsonMutable;
    friend class JsonBasic;
    friend class Json;
public:
    JsonRef &operator=(Json const &json);
    JsonRef &operator=(Json &&json);

    JsonRef(JsonRef const &r) = default;
    JsonRef &operator=(JsonRef const &r) = default;
    // These two make copy as JsonRef is a proxy for reference 
    // and there is no meaning of moving reference
    JsonRef(JsonRef &&r);
    JsonRef &operator=(JsonRef &&r);

    JsonRef &operator+=(Json const& elem);
    JsonRef &operator+=(JsonRef const& elem);
    JsonRef &operator+=(ConstJsonRef const& elem);
protected:
    JsonValuePtr const &Value() const override { return value_ref_; }
    JsonValuePtr &Value() override { return value_ref_; }
private:
    JsonRef(JsonValuePtr& value_ref);

    JsonValuePtr &value_ref_;
};

}

#endif