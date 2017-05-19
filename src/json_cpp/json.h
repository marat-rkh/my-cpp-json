#ifndef __JSON_H__
#define __JSON_H__

#include <string>
#include <memory>
#include <map>
#include <vector>
#include <cstddef>
#include <initializer_list>

#include "json_model.h"
#include "mapping_iterator.h"
#include "json_ref.h"
#include "json_mutable.h"

namespace json_cpp {

class ConstJsonRef;

class Json: public internal::proxy_impl::JsonMutable {
    friend class JsonRef;
    friend class ConstJsonRef;
public:
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

    // these functions are meant to be used as literals 
    // so they have short lower case names
    static Json obj(std::initializer_list<std::pair<const std::string, Json>> const &lst = {});
    static Json arr(std::initializer_list<Json> const &lst = {});
protected:
    JsonValuePtr const &Value() const override { return value_; }
    JsonValuePtr &Value() override { return value_; }
private:
    JsonValuePtr value_;
};

}

#endif