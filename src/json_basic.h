#ifndef __JSON_BASIC_H__
#define __JSON_BASIC_H__

#include <memory>
#include <utility>

#include "json_model.h"
#include "mapping_iterator.h"

namespace json_cpp {

class JsonMutable;
class ConstJsonRef;

// TODO prohibit pointers creation
class JsonBasic {
    friend class JsonMutable;
public:
    using ArraySizeType = inner::json_model::JsonArray::size_type;

    using ObjectConstIterator = 
        inner::utils::MappingIterator<
            inner::json_model::JsonObject::iterator,
            std::pair<std::string const, ConstJsonRef>
        >;
    using ArrayConstIterator =  
        inner::utils::MappingIterator<
            inner::json_model::JsonArray::iterator,
            ConstJsonRef
        >;

    std::string const &AsString() const;
    double AsDouble() const;
    bool AsBool() const;
    std::nullptr_t AsNull() const;

    JType Type() const { 
        auto &val = Value();
        return val ? val->type() : JType::JNULL; 
    }

    ConstJsonRef operator[](std::string const &field_name) const;
    ConstJsonRef operator[](ArraySizeType index) const;

    ObjectConstIterator ObjectBegin() const;
    ObjectConstIterator ObjectEnd() const;

    ArrayConstIterator ArrayBegin() const;
    ArrayConstIterator ArrayEnd() const;
protected:
    using JsonValuePtr = std::shared_ptr<inner::json_model::JsonValue>;

    virtual JsonValuePtr const &Value() const = 0;

    JsonValuePtr const &AccessField(std::string const &field_name) const;
    JsonValuePtr const &AccessElem(ArraySizeType index) const;

    template<typename P>
    static P ProxyElem(JsonValuePtr &ptr) { return P(ptr); }

    template<typename P>
    static std::pair<std::string const, P> ProxyPair(std::pair<std::string const, JsonValuePtr> &p) {
        return std::make_pair(p.first, P(p.second));
    }
};

}

#endif