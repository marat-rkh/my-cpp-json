#ifndef __JSON_CONST_H__
#define __JSON_CONST_H__

#include <utility>

#include "json_basic.h"
#include "json_model.h"
#include "mapping_iterator.h"

namespace json_cpp { namespace internal { namespace proxy_impl {

/*
* P is a proxy type for reference to const json
*/
template<typename P>
class JsonConst: public JsonBasic {
public:
    using ArraySizeType = repr::JsonArray::size_type;

    using ObjectConstIterator = 
        utils::MappingIterator<
            repr::JsonObject::iterator,
            std::pair<std::string const, P>
        >;
    using ArrayConstIterator =  
        utils::MappingIterator<
            repr::JsonArray::iterator,
            P
        >;

    P operator[](std::string const &field_name) const;
    P operator[](ArraySizeType index) const;

    ObjectConstIterator ObjectBegin() const;
    ObjectConstIterator ObjectEnd() const;

    ObjectConstIterator ObjectCBegin() const;
    ObjectConstIterator ObjectCEnd() const;

    ArrayConstIterator ArrayBegin() const;
    ArrayConstIterator ArrayEnd() const;

    ArrayConstIterator ArrayCBegin() const;
    ArrayConstIterator ArrayCEnd() const;
protected:
    virtual P ProxyConstJsonRef(JsonValuePtr &val) const = 0;

    std::pair<std::string const, P> ProxyPair(std::pair<std::string const, JsonValuePtr> &p) const {
        return std::make_pair(p.first, ProxyConstJsonRef(p.second));
    }

    JsonValuePtr const &AccessField(std::string const &field_name) const;
    JsonValuePtr const &AccessElem(ArraySizeType index) const;
};

}}}

#include "json_const.tpp"

#endif