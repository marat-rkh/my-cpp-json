#include "const_json_ref.h"

#include "json.h"
#include "json_ref.h"

namespace json_cpp {

// public

ConstJsonRef::ConstJsonRef(ConstJsonRef &&r)
    : value_ref_(r.value_ref_)
{}

ConstJsonRef::ConstJsonRef(Json const &json)
    : value_ref_(json.value_)
{}

ConstJsonRef::ConstJsonRef(JsonRef const &json_ref)
    : value_ref_(json_ref.value_ref_)
{}

// private

ConstJsonRef::ConstJsonRef(JsonValuePtr const& value_ref)
    : value_ref_(value_ref)
{}

}