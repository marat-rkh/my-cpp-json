#include "json_ref.h"

#include "json.h"
#include "const_json_ref.h"
#include "utils.h"

#include <stdexcept>

using std::shared_ptr;
using std::string;
using std::runtime_error;
using std::nullptr_t;

using namespace json_cpp;
using namespace json_cpp::inner::json_model;

// public

JsonRef &JsonRef::operator=(Json const &json) {
    if(value_ref_ != json.value_) {
        value_ref_ = CopyJsonTree(json.value_);
    }
    return *this;
}

JsonRef &JsonRef::operator=(Json &&json) {
    if(value_ref_ != json.value_) {
        value_ref_ = json.value_;
    }
    return *this;
}

JsonRef::JsonRef(JsonRef &&r)
    : value_ref_(r.value_ref_)
{}

JsonRef &JsonRef::operator=(JsonRef &&r) {
    if(this != &r) {
        value_ref_ = r.value_ref_;
    }
    return *this;
}

ConstJsonRef JsonRef::operator[](string const &field_name) const {
    return ConstJsonRef(AccessField(field_name));
}

JsonRef JsonRef::operator[](string const &field_name) {
    return JsonRef(AccessField(field_name));
}

ConstJsonRef JsonRef::operator[](ArraySizeType index) const {
    return ConstJsonRef(AccessElem(index));
}

JsonRef JsonRef::operator[](ArraySizeType index) {
    return JsonRef(AccessElem(index));
}

// private

JsonRef::JsonRef(shared_ptr<JsonValue>& value_ref)
    : value_ref_(value_ref)
{}