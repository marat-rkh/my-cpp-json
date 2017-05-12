#ifndef __ORDERED_MAP_ITERATOR_H__
#define __ORDERED_MAP_ITERATOR_H__

namespace json_cpp { namespace inner { namespace utils {

/*
* Iterator adapter. Traverses Iter and returns Map entry 
* with the key corresponding to current Iter value.
*/
template<typename Val, typename Map, typename Iter>
class OrderedMapIterator: public std::iterator<std::input_iterator_tag, Val> {
public:
    OrderedMapIterator(Map &m, Iter const &pos)
        : map_(m)
        , pos_(pos)
    {}

    OrderedMapIterator &operator++() {
        ++pos_;
        return *this;
    }

    OrderedMapIterator operator++(int) {
        OrderedMapIterator ret = *this;
        ++pos_;
        return ret;
    }

    bool operator==(OrderedMapIterator const &other) const noexcept {
        return pos_ == other.pos_ && &map_ == &other.map_;
    }

    bool operator!=(OrderedMapIterator const &other) const noexcept { 
        return !(*this == other); 
    }
    
    Val &operator*() const { return *map_.find(*pos_); }
private:
    Map &map_;
    Iter pos_;
};

}}}

#endif