#include "json_accessors.h"

#include "json_ref.h"
#include "utils.h"

#include <stdexcept>

using namespace json_cpp;
using namespace json_cpp::inner::json_model;

using std::string;
using std::shared_ptr;
using std::runtime_error;

inline string InvalidOperation(string const &prefix, JType const &t) {
    return prefix + JTypeUtils::ToString(t);
}

JsonRef JsonAccessors::AccessField(shared_ptr<JsonValue> const &value, string const &field_name) {
    if(value->type() == JType::JOBJECT) {
        return JsonRef(as<JsonObject>(value)->value()[field_name]);
    }
    throw runtime_error(InvalidOperation("attempt to access field on ", value->type()));
}

JsonRef JsonAccessors::AccessElem(shared_ptr<JsonValue> const &value, size_type index) {
    if(value->type() == JType::JARRAY) {
        return JsonRef(as<JsonArray>(value)->value()[index]);
    }
    throw runtime_error(InvalidOperation("attempt to index ", value->type()));
}