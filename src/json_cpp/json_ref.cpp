#include "json_ref.h"

#include <stdexcept>

#include "json.h"
#include "const_json_ref.h"

using std::shared_ptr;
using std::string;
using std::runtime_error;
using std::nullptr_t;

using json_cpp::internal::repr::JsonValue;
using json_cpp::internal::repr::CopyJsonTree;

namespace json_cpp {

// public

JsonRef::JsonRef(JsonRef &&r)
    : value_ref_(r.value_ref_)
{}

JsonRef &JsonRef::operator=(JsonRef &&r) {
    if(this != &r) {
        value_ref_ = r.value_ref_;
    }
    return *this;
}

JsonRef::JsonRef(Json &json)
    : value_ref_(json.value_)
{}

JsonRef &JsonRef::operator=(Json const &json) {
    if(value_ref_ != json.value_) {
        value_ref_ = CopyJsonTree(json.value_);
    }
    return *this;
}

JsonRef &JsonRef::operator=(ConstJsonRef const &const_json_ref) {
    if(value_ref_ != const_json_ref.value_ref_) {
        value_ref_ = CopyJsonTree(const_json_ref.value_ref_);
    }
    return *this;
}

JsonRef &JsonRef::operator+=(Json const& elem) {
    AddElemToArray(elem.value_);
    return *this;
}
JsonRef &JsonRef::operator+=(JsonRef const& elem) {
    AddElemToArray(elem.value_ref_);
    return *this;
}
JsonRef &JsonRef::operator+=(ConstJsonRef const& elem) {
    AddElemToArray(elem.value_ref_);
    return *this;
}

// protected

ConstJsonRef JsonRef::ProxyConstJsonRef(JsonValuePtr &val) const { 
    return ConstJsonRef(val); 
}

// private

JsonRef::JsonRef(shared_ptr<JsonValue>& value_ref)
    : value_ref_(value_ref)
{}

}