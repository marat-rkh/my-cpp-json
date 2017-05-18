#include "json_mutable.h"

#include "json_ref.h"

using namespace json_cpp;

using std::string;

JsonRef JsonMutable::operator[](string const &field_name) {
    auto &r = const_cast<JsonValuePtr &>(static_cast<JsonMutable const &>(*this).AccessField(field_name));
    return JsonRef(r);
}

JsonRef JsonMutable::operator[](ArraySizeType index) {
    auto &r = const_cast<JsonValuePtr &>(static_cast<JsonMutable const &>(*this).AccessElem(index));
    return JsonRef(r);
}