#ifndef __JSON_MUTABLE_H__
#define __JSON_MUTABLE_H__

#include "json_basic.h"

namespace json_cpp {

// TODO prohibit pointers creation
class JsonMutable: public JsonBasic {
protected:
    virtual JsonValuePtr &Value() = 0;

    using JsonBasic::AccessField; // const version
    JsonValuePtr &AccessField(std::string const &field_name);
    using JsonBasic::AccessElem; // const version
    JsonValuePtr &AccessElem(ArraySizeType index);
};

}

#endif