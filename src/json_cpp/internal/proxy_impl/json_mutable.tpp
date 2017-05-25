#include <string>
#include <functional>

namespace json_cpp { namespace internal { namespace proxy_impl {

template<typename P, typename CP>
P JsonMutable<P, CP>::operator[](std::string const &field_name) {
    auto &r = const_cast<JsonValuePtr &>(static_cast<JsonMutable<P, CP> const &>(*this).AccessField(field_name));
    return ProxyJsonRef(r);
}

template<typename P, typename CP>
P JsonMutable<P, CP>::operator[](ArraySizeType index) {
    auto &r = const_cast<JsonValuePtr &>(static_cast<JsonMutable<P, CP> const &>(*this).AccessElem(index));
    return ProxyJsonRef(r);
}

template<typename P, typename CP>
typename JsonMutable<P, CP>::ObjectIterator JsonMutable<P, CP>::ObjectBegin() {
    return this->template ApplyToValueAs<repr::JsonObject>(
        "get object iterator",
        [this](std::shared_ptr<repr::JsonObject> const &o) {
            return utils::MakeMappingBegin(
                o->value().begin(),
                std::bind(&JsonMutable<P, CP>::ProxyPair, this, std::placeholders::_1)
            );
        }
    );  
}

template<typename P, typename CP>
typename JsonMutable<P, CP>::ObjectIterator JsonMutable<P, CP>::ObjectEnd() {
    return this->template ApplyToValueAs<repr::JsonObject>(
        "get object iterator",
        [this](std::shared_ptr<repr::JsonObject> const &o) {
            return utils::MakeMappingEnd(
                o->value().end(),
                std::bind(&JsonMutable<P, CP>::ProxyPair, this, std::placeholders::_1)
            );
        }
    );
}

template<typename P, typename CP>
typename JsonMutable<P, CP>::ArrayIterator JsonMutable<P, CP>::ArrayBegin() {
    return this->template ApplyToValueAs<repr::JsonArray>(
        "get array iterator",
        [this](std::shared_ptr<repr::JsonArray> const &a) {
            return utils::MakeMappingBegin(
                a->value().begin(),
                std::bind(&JsonMutable<P, CP>::ProxyJsonRef, this, std::placeholders::_1)
            );
        }
    );
}

template<typename P, typename CP>
typename JsonMutable<P, CP>::ArrayIterator JsonMutable<P, CP>::ArrayEnd() {
    return this->template ApplyToValueAs<repr::JsonArray>(
        "get array iterator",
        [this](std::shared_ptr<repr::JsonArray> const &a) {
            return utils::MakeMappingEnd(
                a->value().end(),
                std::bind(&JsonMutable<P, CP>::ProxyJsonRef, this, std::placeholders::_1)
            );
        }
    );
}

// protected

template<typename P, typename CP>
void JsonMutable<P, CP>::AddElemToArray(JsonValuePtr const &elem) {
    return this->template ApplyToValueAs<repr::JsonArray>(
        "append element to json array",
        [&](std::shared_ptr<repr::JsonArray> const &a) { a->value().push_back(CopyJsonTree(elem)); }
    );
}

}}}