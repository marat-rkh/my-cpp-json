#ifndef __UTILS_H__
#define __UTILS_H__

#include <memory>

namespace json_cpp {

// TODO remove this wrapper. It is only used in json_basic.h.
// JsonParserResult also needs it, but JsonParserResult must be
// replaced with exception mechanism.
template<typename D, typename B> 
std::shared_ptr<D> as(std::shared_ptr<B> const &v) {
    return std::dynamic_pointer_cast<D>(v);
}

}

#endif