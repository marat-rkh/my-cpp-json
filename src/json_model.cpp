#include "json_model.h"
#include "json.h"

#include <stdexcept>

using namespace json_cpp;
using namespace json_cpp::inner::json_model;

std::string JTypeUtils::ToString(JType const &t) {
    switch(t) {
        case JType::JSTRING: return "JSTRING";
        case JType::JNUMBER: return "JNUMBER";
        case JType::JOBJECT: return "JOBJECT";
        case JType::JARRAY: return "JARRAY";
        case JType::JBOOL: return "JBOOL";
        case JType::JNULL: return "JNULL";
        default:
            throw std::runtime_error("unexcepted JType enum value");
    }
}

JsonObject::JsonObject(std::initializer_list<std::pair<const std::string, Json>> const &lst)
    : value_(lst)
{}

JsonArray::JsonArray(std::initializer_list<Json> const &lst)
    : value_(lst)
{}