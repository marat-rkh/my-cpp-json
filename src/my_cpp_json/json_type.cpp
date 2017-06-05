#include "json_type.h"

#include <stdexcept>

using std::string;
using std::runtime_error;

namespace my_cpp_json {

string JTypeUtils::ToString(JType const &t) {
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

}