#ifndef __JSON_MUTABLE_H__
#define __JSON_MUTABLE_H__

#include "json_basic.h"

namespace json_cpp {

class JsonRef;

// TODO prohibit pointers creation
class JsonMutable: public JsonBasic {
public:
    using JsonBasic::operator[]; // const version
    JsonRef operator[](std::string const &field_name);

    using JsonBasic::operator[]; // const version
    JsonRef operator[](ArraySizeType index);
protected:
    virtual JsonValuePtr &Value() = 0;
};

}

#endif