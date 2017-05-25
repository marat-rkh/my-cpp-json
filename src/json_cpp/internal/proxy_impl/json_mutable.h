#ifndef __JSON_MUTABLE_H__
#define __JSON_MUTABLE_H__

#include "json_const.h"
#include "mapping_iterator.h"

namespace json_cpp { namespace internal { namespace proxy_impl {

// TODO prohibit pointers creation
/*
* P is a proxy type for reference to json, CP -- to const json
*/
template<typename P, typename CP>
class JsonMutable: public JsonConst<CP> {
public:
    using typename JsonConst<CP>::ArraySizeType;

    using ObjectIterator = 
        utils::MappingIterator<
            repr::JsonObject::iterator,
            std::pair<std::string const, P>
        >;
    using ArrayIterator =  
        utils::MappingIterator<
            repr::JsonArray::iterator,
            P
        >;

    using JsonConst<CP>::operator[];

    P operator[](std::string const &field_name) {
        auto &r = const_cast<JsonValuePtr &>(static_cast<JsonMutable<P, CP> const &>(*this).AccessField(field_name));
        return ProxyJsonRef(r);
    }

    P operator[](ArraySizeType index) {
        auto &r = const_cast<JsonValuePtr &>(static_cast<JsonMutable<P, CP> const &>(*this).AccessElem(index));
        return ProxyJsonRef(r);
    }

    using JsonConst<CP>::ObjectBegin;
    using JsonConst<CP>::ObjectEnd;
    using JsonConst<CP>::ArrayBegin;
    using JsonConst<CP>::ArrayEnd;

    ObjectIterator ObjectBegin() {
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
    ObjectIterator ObjectEnd() {
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

    ArrayIterator ArrayBegin() {
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

    ArrayIterator ArrayEnd() {
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
protected:
    using typename JsonConst<CP>::JsonValuePtr;

    virtual JsonValuePtr &Value() = 0;

    virtual P ProxyJsonRef(JsonValuePtr &val) = 0;

    std::pair<std::string const, P> ProxyPair(std::pair<std::string const, JsonValuePtr> &p) {
        return std::make_pair(p.first, ProxyJsonRef(p.second));
    }

    void AddElemToArray(JsonValuePtr const &elem) {
        return this->template ApplyToValueAs<repr::JsonArray>(
            "append element to json array",
            [&](std::shared_ptr<repr::JsonArray> const &a) { a->value().push_back(CopyJsonTree(elem)); }
        );
    }
};

}}}

#endif