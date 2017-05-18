#ifndef __JSON_H__
#define __JSON_H__

#include <string>
#include <memory>
#include <map>
#include <vector>
#include <cstddef>
#include <initializer_list>

#include "json_model.h"
#include "utils.h"
#include "mapping_iterator.h"
#include "json_ref.h"
#include "json_mutable.h"

namespace json_cpp {

class ConstJsonRef;

class Json: public JsonMutable {
    friend class JsonRef;
private:
    template<typename V>
    using ObjectEntry = std::pair<std::string const, V>;
public:
    using object_iterator = 
        inner::utils::MappingIterator<
            inner::json_model::JsonObject::iterator,
            ObjectEntry<JsonRef>
        >;
    using object_const_iterator = 
        inner::utils::MappingIterator<
            inner::json_model::JsonObject::iterator,
            ObjectEntry<JsonRef const>
        >;
    using array_iterator = 
        inner::utils::MappingIterator<
            typename inner::json_model::JsonArray::iterator,
            JsonRef
        >;
    using array_const_iterator =  
        inner::utils::MappingIterator<
            typename inner::json_model::JsonArray::iterator,
            JsonRef const
        >;

    Json() = default;
    Json(std::nullptr_t np): Json() {}
    Json(std::string const& str);
    Json(char const *c_str): Json(std::string(c_str)) {}
    Json(double num);
    Json(int num): Json(static_cast<double>(num)) {}
    Json(bool b);
    Json(std::initializer_list<std::pair<const std::string, Json>> const &lst);
    Json(JsonRef const &json_ref);

    Json(Json const&other);
    Json(Json &&other) noexcept;
    ~Json();

    Json &operator=(Json const &other);
    Json &operator=(Json &&other) noexcept;

    Json &operator+=(Json const& elem);
    Json &operator+=(JsonRef const& elem);
    Json &operator+=(ConstJsonRef const& elem);

    object_iterator ObjectBegin();
    object_const_iterator ObjectBegin() const;
    object_iterator ObjectEnd();
    object_const_iterator ObjectEnd() const;

    array_iterator ArrayBegin();
    array_const_iterator ArrayBegin() const;
    array_iterator ArrayEnd();
    array_const_iterator ArrayEnd() const;

    // these functions are meant to be used as literals 
    // so they have short lower case names
    static Json obj(std::initializer_list<std::pair<const std::string, Json>> const &lst = {});
    static Json arr(std::initializer_list<Json> const &lst = {});
protected:
    JsonValuePtr const &Value() const override { return value_; }
    JsonValuePtr &Value() override { return value_; }
private:
    JsonValuePtr value_;

    static ObjectEntry<JsonRef> ProxyEntry(ObjectEntry<JsonValuePtr> &p) {
        return std::make_pair(p.first, JsonRef(p.second));
    }
    static ObjectEntry<JsonRef const> ProxyEntryConst(ObjectEntry<JsonValuePtr> &p) {
        return std::make_pair(p.first, JsonRef(p.second));
    }

    static JsonRef Proxy(JsonValuePtr &ptr) { return JsonRef(ptr); }
    static JsonRef const ProxyConst(JsonValuePtr &ptr) { return JsonRef(ptr); }
};

}

#endif