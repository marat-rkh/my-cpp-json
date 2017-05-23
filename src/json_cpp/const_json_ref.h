#ifndef __CONST_JSON_REF_H__
#define __CONST_JSON_REF_H__ 

#include "json_basic.h"

namespace json_cpp {

class Json;
class JsonRef;

class ConstJsonRef: public internal::proxy_impl::JsonBasic {
    friend internal::proxy_impl::JsonBasic;
    friend Json;
    friend JsonRef;
public:
    // can copy const ref
    ConstJsonRef(ConstJsonRef const &r) = default;
    // moving is implemente as copy as there is no meaning of ref moving
    ConstJsonRef(ConstJsonRef &&r);

    ConstJsonRef(Json const &json);
    // forbidden, as ConstJsonRef only holds ref 
    // and storing ref to members of tmp object is a bad idea
    ConstJsonRef(Json &&) = delete;
    ConstJsonRef(JsonRef const &json_ref);
protected:
    JsonValuePtr const &Value() const override { return value_ref_; }
private:
    ConstJsonRef(JsonValuePtr const& value_ref);

    JsonValuePtr const &value_ref_;
};

}

#endif