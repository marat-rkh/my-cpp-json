#include "const_json_ref.h"

using namespace json_cpp;

// public

ConstJsonRef::ConstJsonRef(ConstJsonRef &&r)
    : value_ref_(r.value_ref_)
{}

// private

ConstJsonRef::ConstJsonRef(JsonValuePtr const& value_ref)
    : value_ref_(value_ref)
{}