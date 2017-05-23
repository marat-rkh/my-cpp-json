#ifndef __JSON_BASIC_H__
#define __JSON_BASIC_H__

#include <memory>
#include <utility>
#include <type_traits>
#include <stdexcept>

#include "json_type.h"
#include "json_model.h"
#include "mapping_iterator.h"

namespace json_cpp { 

class ConstJsonRef;

namespace internal { namespace proxy_impl {

class JsonMutable;

// TODO prohibit pointers creation
class JsonBasic {
    friend class JsonMutable;
public:
    using ArraySizeType = repr::JsonArray::size_type;

    using ObjectConstIterator = 
        utils::MappingIterator<
            repr::JsonObject::iterator,
            std::pair<std::string const, ConstJsonRef>
        >;
    using ArrayConstIterator =  
        utils::MappingIterator<
            repr::JsonArray::iterator,
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

    ObjectConstIterator ObjectCBegin() const;
    ObjectConstIterator ObjectCEnd() const;

    ArrayConstIterator ArrayBegin() const;
    ArrayConstIterator ArrayEnd() const;

    ArrayConstIterator ArrayCBegin() const;
    ArrayConstIterator ArrayCEnd() const;
protected:
    using JsonValuePtr = std::shared_ptr<repr::JsonValue>;

    virtual JsonValuePtr const &Value() const = 0;

    JsonValuePtr const &AccessField(std::string const &field_name) const;
    JsonValuePtr const &AccessElem(ArraySizeType index) const;

    template<typename P>
    static P ProxyElem(JsonValuePtr &ptr) { return P(ptr); }

    template<typename P>
    static std::pair<std::string const, P> ProxyPair(std::pair<std::string const, JsonValuePtr> &p) {
        return std::make_pair(p.first, P(p.second));
    }

    // Casts result of Value() (of type shared_ptr<JsonValue>) to shared_ptr<T>
    // and applies function of type F to the cast result. If dynamic type of JsonValue 
    // is not T, throws exception.
    template<typename T, typename F>
    auto ApplyToValueAs(std::string const &action_name, F func) const ->
        typename std::result_of<F(std::shared_ptr<T> &)>::type
    {
        auto &val = Value();
        if(!val || val->type() != repr::GetJType<T>::value) {
            throw std::runtime_error(InvalidAction(val->type(), action_name));
        }
        return func(std::dynamic_pointer_cast<T>(val));
    }

    static std::string InvalidAction(JType const &t, std::string const &descr);
};

}}}

#endif