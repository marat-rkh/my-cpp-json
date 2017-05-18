#include "json_ref.h"

#include "json.h"
#include "utils.h"

#include <stdexcept>

using std::shared_ptr;
using std::string;
using std::runtime_error;
using std::nullptr_t;

using namespace json_cpp;
using namespace json_cpp::inner::json_model;

JsonRef::JsonRef(shared_ptr<JsonValue>& value_ref)
    : value_ref_(value_ref)
{}

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

JsonRef const JsonRef::operator[](string const &field_name) const {
    return JsonAccessors::AccessField(value_ref_, field_name);
}

JsonRef JsonRef::operator[](string const &field_name) {
    return JsonAccessors::AccessField(value_ref_, field_name);
}

JsonRef const JsonRef::operator[](size_type index) const {
    return JsonAccessors::AccessElem(value_ref_, index);
}

JsonRef JsonRef::operator[](size_type index) {
    return JsonAccessors::AccessElem(value_ref_, index);
}