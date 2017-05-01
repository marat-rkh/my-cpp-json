#ifndef __UTILS_H__
#define __UTILS_H__

#include <memory>

namespace json_cpp {

template<typename B, typename D> 
std::shared_ptr<D> as(std::shared_ptr<B> v) {
    return std::dynamic_pointer_cast<D>(v);
}

}

#endif