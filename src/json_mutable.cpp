#include "json_mutable.h"

using namespace json_cpp;

JsonMutable::JsonValuePtr &JsonMutable::AccessField(std::string const &field_name) {
    return const_cast<JsonValuePtr &>(static_cast<JsonMutable const &>(*this).AccessField(field_name));
}

JsonMutable::JsonValuePtr &JsonMutable::AccessElem(ArraySizeType index) {
    return const_cast<JsonValuePtr &>(static_cast<JsonMutable const &>(*this).AccessElem(index));
}