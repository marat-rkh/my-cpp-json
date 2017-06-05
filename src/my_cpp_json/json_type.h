#ifndef __JSON_TYPE_H__
#define __JSON_TYPE_H__

#include <string>

namespace my_cpp_json {

enum class JType {
    JSTRING,
    JNUMBER,
    JOBJECT,
    JARRAY,
    JBOOL,
    JNULL
};

class JTypeUtils {
public:
    static std::string ToString(JType const &t);
};

}

#endif