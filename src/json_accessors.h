#ifndef __JSON_ACCESSORS_H__
#define __JSON_ACCESSORS_H__

#include <memory>
#include <string>

#include "json_model.h"

namespace json_cpp {

class JsonRef;

class JsonAccessors {
public:
    using size_type = inner::json_model::JsonArray::size_type;

    static JsonRef AccessField(
        std::shared_ptr<inner::json_model::JsonValue> const &value,
        std::string const &field_name
    );

    static JsonRef AccessElem(
        std::shared_ptr<inner::json_model::JsonValue> const &value,
        size_type index
    );
};

}

#endif