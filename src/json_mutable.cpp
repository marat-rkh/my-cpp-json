#include "json_mutable.h"

#include "utils.h"
#include "json_ref.h"
#include "json_model.h"

#include <stdexcept>

using namespace json_cpp;
using namespace json_cpp::inner::json_model;

using std::string;

JsonRef JsonMutable::operator[](string const &field_name) {
    auto &r = const_cast<JsonValuePtr &>(static_cast<JsonMutable const &>(*this).AccessField(field_name));
    return JsonRef(r);
}

JsonRef JsonMutable::operator[](ArraySizeType index) {
    auto &r = const_cast<JsonValuePtr &>(static_cast<JsonMutable const &>(*this).AccessElem(index));
    return JsonRef(r);
}

inline string InvalidOperation(string const &prefix, JType const &t) {
    return prefix + JTypeUtils::ToString(t);
}

void JsonMutable::AddElemToArray(JsonBasic const &elem) {
    auto &val = Value();
    if(val->type() == JType::JARRAY) {
        as<JsonArray>(val)->value().push_back(CopyJsonTree(elem.Value()));
        return;
    }
    throw std::runtime_error(InvalidOperation("attempt to append element to ", val->type()));
}