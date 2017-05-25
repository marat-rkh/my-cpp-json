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

    P operator[](std::string const &field_name);
    P operator[](ArraySizeType index);

    using JsonConst<CP>::ObjectBegin;
    using JsonConst<CP>::ObjectEnd;
    
    using JsonConst<CP>::ArrayBegin;
    using JsonConst<CP>::ArrayEnd;

    ObjectIterator ObjectBegin();
    ObjectIterator ObjectEnd();

    ArrayIterator ArrayBegin();
    ArrayIterator ArrayEnd();
protected:
    using typename JsonConst<CP>::JsonValuePtr;

    virtual JsonValuePtr &Value() = 0;

    virtual P ProxyJsonRef(JsonValuePtr &val) = 0;

    std::pair<std::string const, P> ProxyPair(std::pair<std::string const, JsonValuePtr> &p) {
        return std::make_pair(p.first, ProxyJsonRef(p.second));
    }

    void AddElemToArray(JsonValuePtr const &elem);
};

}}}

#include "json_mutable.tpp"

#endif