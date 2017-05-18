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
#include "json_accessors.h"
#include "json_basic.h"

namespace json_cpp {

class JsonRef;

class Json: public JsonBasic {
    friend class JsonRef;
private:
    template<typename V>
    using ObjectEntry = std::pair<std::string const, V>;
public:
    using size_type = JsonAccessors::size_type;
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

    JsonRef const operator[](std::string const &field_name) const;
    JsonRef operator[](std::string const &field_name);

    JsonRef const operator[](size_type index) const;
    JsonRef operator[](size_type index);

    Json &operator+=(Json const& val);

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
    std::shared_ptr<inner::json_model::JsonValue> &Value() override { return value_; }
    std::shared_ptr<inner::json_model::JsonValue> const &Value() const override { return value_; }
private:
    using JsonValuePtr = std::shared_ptr<inner::json_model::JsonValue>;

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