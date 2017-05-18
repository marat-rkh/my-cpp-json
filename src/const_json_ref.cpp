#include "const_json_ref.h"

using namespace json_cpp;

// public

ConstJsonRef::ConstJsonRef(ConstJsonRef &&r)
    : value_ref_(r.value_ref_)
{}

ConstJsonRef ConstJsonRef::operator[](std::string const &field_name) const {
    return ConstJsonRef(AccessField(field_name));
}
    
ConstJsonRef ConstJsonRef::operator[](ArraySizeType index) const {
    return ConstJsonRef(AccessElem(index));
}

// private

ConstJsonRef::ConstJsonRef(JsonValuePtr const& value_ref)
    : value_ref_(value_ref)
{}