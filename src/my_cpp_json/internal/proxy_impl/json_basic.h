#ifndef __JSON_BASIC_H__
#define __JSON_BASIC_H__

#include <memory>
#include <type_traits>
#include <stdexcept>

#include "json_type.h"
#include "json_model.h"

namespace my_cpp_json { namespace internal { namespace proxy_impl {

// TODO prohibit pointers creation
class JsonBasic {
public:
    std::string const &AsString() const;
    double AsDouble() const;
    bool AsBool() const;
    std::nullptr_t AsNull() const;

    JType Type() const { 
        auto &val = Value();
        return val ? val->type() : JType::JNULL; 
    }
protected:
    using JsonValuePtr = std::shared_ptr<repr::JsonValue>;

    virtual JsonValuePtr const &Value() const = 0;

    // Casts result of Value().get() (of type JsonValue*) to T*
    // and applies function of type F to the cast result. If dynamic type of JsonValue 
    // is not T, throws exception.
    template<typename T, typename F>
    auto ApplyToValueAs(std::string const &action_name, F func) const ->
        typename std::result_of<F(T*)>::type
    {
        auto &val = Value();
        if(!val || val->type() != repr::GetJType<T>::value) {
            throw std::runtime_error(InvalidAction(val->type(), action_name));
        }
        return func(dynamic_cast<T*>(val.get()));
    }

    static std::string InvalidAction(JType const &t, std::string const &descr);
};

}}}

#endif