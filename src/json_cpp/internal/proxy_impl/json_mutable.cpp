#include "json_mutable.h"

#include <stdexcept>

#include "json_ref.h"
#include "json_model.h"

using std::string;
using std::runtime_error;
using std::shared_ptr;

using json_cpp::internal::repr::JsonObject;
using json_cpp::internal::repr::JsonArray;
using json_cpp::internal::utils::MakeMappingBegin;
using json_cpp::internal::utils::MakeMappingEnd;

namespace json_cpp { namespace internal { namespace proxy_impl {

JsonRef JsonMutable::operator[](string const &field_name) {
    auto &r = const_cast<JsonValuePtr &>(static_cast<JsonMutable const &>(*this).AccessField(field_name));
    return JsonRef(r);
}

JsonRef JsonMutable::operator[](ArraySizeType index) {
    auto &r = const_cast<JsonValuePtr &>(static_cast<JsonMutable const &>(*this).AccessElem(index));
    return JsonRef(r);
}

JsonMutable::ObjectIterator JsonMutable::ObjectBegin() {
    return ApplyToValueAs<JsonObject>(
        "get object iterator",
        [](shared_ptr<JsonObject> const &o) {
            return MakeMappingBegin(o->value().begin(), &JsonBasic::ProxyPair<JsonRef>);
        }
    );
}

JsonMutable::ObjectIterator JsonMutable::ObjectEnd() {
    return ApplyToValueAs<JsonObject>(
        "get object iterator",
        [](shared_ptr<JsonObject> const &o) {
            return MakeMappingEnd(o->value().end(), &JsonBasic::ProxyPair<JsonRef>);
        }
    );
}

JsonMutable::ArrayIterator JsonMutable::ArrayBegin() {
    return ApplyToValueAs<JsonArray>(
        "get array iterator",
        [](shared_ptr<JsonArray> const &a) {
            return MakeMappingBegin(a->value().begin(), &JsonBasic::ProxyElem<JsonRef>);
        }
    );
}

JsonMutable::ArrayIterator JsonMutable::ArrayEnd() {
    return ApplyToValueAs<JsonArray>(
        "get array iterator",
        [](shared_ptr<JsonArray> const &a) {
            return MakeMappingEnd(a->value().end(), &JsonBasic::ProxyElem<JsonRef>);
        }
    );
}

// protected

void JsonMutable::AddElemToArray(JsonValuePtr const &elem) {
    return ApplyToValueAs<JsonArray>(
        "append element to json array",
        [&](shared_ptr<JsonArray> const &a) { a->value().push_back(CopyJsonTree(elem)); }
    );
}

}}}