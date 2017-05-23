#include "json_basic.h"

#include <string>

#include "const_json_ref.h"

using std::string;
using std::nullptr_t;
using std::runtime_error;
using std::shared_ptr;

using json_cpp::internal::repr::JsonString;
using json_cpp::internal::repr::JsonNumber;
using json_cpp::internal::repr::JsonBool;
using json_cpp::internal::repr::JsonObject;
using json_cpp::internal::repr::JsonArray;
using json_cpp::internal::utils::MakeMappingBegin;
using json_cpp::internal::utils::MakeMappingEnd;

namespace json_cpp { namespace internal { namespace proxy_impl {

string const &JsonBasic::AsString() const {
    return ApplyToValueAs<JsonString>(
        "convert to string",
        [](shared_ptr<JsonString> const &s) -> string const & { return s->value(); }
    );
}

double JsonBasic::AsDouble() const {
    return ApplyToValueAs<JsonNumber>(
        "convert to double",
        [](shared_ptr<JsonNumber> const &n) { return n->value(); }
    );
}

bool JsonBasic::AsBool() const {
    return ApplyToValueAs<JsonBool>(
        "convert to bool",
        [](shared_ptr<JsonBool> const &b) { return b->value(); }
    );
}

nullptr_t JsonBasic::AsNull() const {
    auto &val = Value();
    if(val) {
        throw runtime_error(InvalidAction(val->type(), "convert to nullptr"));
    }
    return nullptr;
}

ConstJsonRef JsonBasic::operator[](std::string const &field_name) const {
    return ConstJsonRef(AccessField(field_name));
}
    
ConstJsonRef JsonBasic::operator[](ArraySizeType index) const {
    return ConstJsonRef(AccessElem(index));
}

JsonBasic::ObjectConstIterator JsonBasic::ObjectBegin() const {
    return ApplyToValueAs<JsonObject>(
        "get object iterator",
        [](shared_ptr<JsonObject> const &o) {
            return MakeMappingBegin(o->value().begin(), &JsonBasic::ProxyPair<ConstJsonRef>);
        }
    );
}

JsonBasic::ObjectConstIterator JsonBasic::ObjectEnd() const {
    return ApplyToValueAs<JsonObject>(
        "get object iterator",
        [](shared_ptr<JsonObject> const &o) {
            return MakeMappingEnd(o->value().end(), &JsonBasic::ProxyPair<ConstJsonRef>);
        }
    );
}

JsonBasic::ObjectConstIterator JsonBasic::ObjectCBegin() const { return ObjectCBegin(); }
JsonBasic::ObjectConstIterator JsonBasic::ObjectCEnd() const { return ObjectEnd(); }

JsonBasic::ArrayConstIterator JsonBasic::ArrayBegin() const {
    return ApplyToValueAs<JsonArray>(
        "get array iterator",
        [](shared_ptr<JsonArray> const &a) {
            return MakeMappingBegin(a->value().begin(), &JsonBasic::ProxyElem<ConstJsonRef>);
        }
    );
}

JsonBasic::ArrayConstIterator JsonBasic::ArrayEnd() const {
    return ApplyToValueAs<JsonArray>(
        "get array iterator",
        [](shared_ptr<JsonArray> const &a) {
            return MakeMappingEnd(a->value().end(), &JsonBasic::ProxyElem<ConstJsonRef>);
        }
    );
}

JsonBasic::ArrayConstIterator JsonBasic::ArrayCBegin() const { return ArrayBegin(); }
JsonBasic::ArrayConstIterator JsonBasic::ArrayCEnd() const { return ArrayEnd(); }

// protected

JsonBasic::JsonValuePtr const &JsonBasic::AccessField(string const &field_name) const {
    return ApplyToValueAs<JsonObject>(
        "access json object field",
        [&](shared_ptr<JsonObject> const &o) -> JsonValuePtr const & { return o->value()[field_name]; }
    );
}

JsonBasic::JsonValuePtr const &JsonBasic::AccessElem(ArraySizeType index) const {
    return ApplyToValueAs<JsonArray>(
        "access json array element",
        [&](shared_ptr<JsonArray> const &a) -> JsonValuePtr const & { return a->value()[index]; }
    );
}

inline string JsonBasic::InvalidAction(JType const &t, string const &descr) {
    return "invalid action on type " + JTypeUtils::ToString(t) + ": " + descr;
}

}}}