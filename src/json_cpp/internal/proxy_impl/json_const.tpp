#include <string>
#include <functional>

namespace json_cpp { namespace internal { namespace proxy_impl {

template<typename P>
P JsonConst<P>::operator[](std::string const &field_name) const {
    return ProxyConstJsonRef(AccessField(field_name));
}
    
template<typename P>
P JsonConst<P>::operator[](ArraySizeType index) const {
    return ProxyConstJsonRef(AccessElem(index));
}

template<typename P>
typename JsonConst<P>::ObjectConstIterator JsonConst<P>::ObjectBegin() const {
    return ApplyToValueAs<repr::JsonObject>(
        "get object iterator",
        [this](repr::JsonObject *o) {
            return utils::MakeMappingBegin(
                o->value().begin(),
                std::bind(&JsonConst<P>::ProxyPair, this, std::placeholders::_1)
            );
        }
    );
}

template<typename P>
typename JsonConst<P>::ObjectConstIterator JsonConst<P>::ObjectEnd() const {
    return ApplyToValueAs<repr::JsonObject>(
        "get object iterator",
        [this](repr::JsonObject *o) {
            return utils::MakeMappingEnd(
                o->value().end(),
                std::bind(&JsonConst<P>::ProxyPair, this, std::placeholders::_1)
            );
        }
    );
}

template<typename P>
typename JsonConst<P>::ObjectConstIterator JsonConst<P>::ObjectCBegin() const { return ObjectCBegin(); }
template<typename P>
typename JsonConst<P>::ObjectConstIterator JsonConst<P>::ObjectCEnd() const { return ObjectEnd(); }

template<typename P>
typename JsonConst<P>::ArrayConstIterator JsonConst<P>::ArrayBegin() const {
    return ApplyToValueAs<repr::JsonArray>(
        "get array iterator",
        [this](repr::JsonArray *a) {
            return utils::MakeMappingBegin(
                a->value().begin(),
                std::bind(&JsonConst<P>::ProxyConstJsonRef, this, std::placeholders::_1)
            );
        }
    );
}

template<typename P>
typename JsonConst<P>::ArrayConstIterator JsonConst<P>::ArrayEnd() const {
    return ApplyToValueAs<repr::JsonArray>(
        "get array iterator",
        [this](repr::JsonArray *a) {
            return utils::MakeMappingEnd(
                a->value().end(),
                std::bind(&JsonConst<P>::ProxyConstJsonRef, this, std::placeholders::_1)
            );
        }
    );
}

template<typename P>
typename JsonConst<P>::ArrayConstIterator JsonConst<P>::ArrayCBegin() const { return ArrayBegin(); }
template<typename P>
typename JsonConst<P>::ArrayConstIterator JsonConst<P>::ArrayCEnd() const { return ArrayEnd(); }

// protected

template<typename P>
typename JsonConst<P>::JsonValuePtr const &JsonConst<P>::AccessField(std::string const &field_name) const {
    return ApplyToValueAs<repr::JsonObject>(
        "access json object field",
        [&](repr::JsonObject *o) -> JsonValuePtr const & { 
            return o->value()[field_name]; 
        }
    );
}

template<typename P>
typename JsonConst<P>::JsonValuePtr const &JsonConst<P>::AccessElem(ArraySizeType index) const {
    return ApplyToValueAs<repr::JsonArray>(
        "access json array element",
        [&](repr::JsonArray *a) -> JsonValuePtr const & { return a->value()[index]; }
    );
}

}}}