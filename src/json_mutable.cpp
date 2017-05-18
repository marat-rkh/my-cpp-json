#include "json_mutable.h"

#include "utils.h"
#include "json_ref.h"
#include "json_model.h"

#include <stdexcept>

using namespace json_cpp;
using namespace json_cpp::inner::json_model;
using namespace json_cpp::inner::utils;

using std::string;
using std::runtime_error;

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

JsonMutable::ObjectIterator JsonMutable::ObjectBegin() {
    auto &val = Value();
    if(val->type() == JType::JOBJECT) {
        return MakeMappingBegin(as<JsonObject>(val)->value().begin(), &JsonBasic::ProxyPair<JsonRef>);
    }
    throw runtime_error(InvalidOperation("attempt to access object iterator on ", val->type()));
}

JsonMutable::ObjectIterator JsonMutable::ObjectEnd() {
    auto &val = Value();
    if(val->type() == JType::JOBJECT) {
        return MakeMappingEnd(as<JsonObject>(val)->value().end(), &JsonBasic::ProxyPair<JsonRef>);
    }
    throw runtime_error(InvalidOperation("attempt to access object iterator on ", val->type()));
}

JsonMutable::ArrayIterator JsonMutable::ArrayBegin() {
    auto &val = Value();
    if(val->type() == JType::JARRAY) {
        return MakeMappingBegin(as<JsonArray>(val)->value().begin(), &JsonBasic::ProxyElem<JsonRef>);
    }
    throw runtime_error(InvalidOperation("attempt to access array iterator on ", val->type()));
}

JsonMutable::ArrayIterator JsonMutable::ArrayEnd() {
    auto &val = Value();
    if(val->type() == JType::JARRAY) {
        return MakeMappingEnd(as<JsonArray>(val)->value().end(), &JsonBasic::ProxyElem<JsonRef>);
    }
    throw runtime_error(InvalidOperation("attempt to access array iterator on ", val->type()));
}

// protected

void JsonMutable::AddElemToArray(JsonBasic const &elem) {
    auto &val = Value();
    if(val->type() == JType::JARRAY) {
        as<JsonArray>(val)->value().push_back(CopyJsonTree(elem.Value()));
        return;
    }
    throw runtime_error(InvalidOperation("attempt to append element to ", val->type()));
}