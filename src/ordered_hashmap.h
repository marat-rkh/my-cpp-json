#ifndef __ORDERED_HASHMAP_H__
#define __ORDERED_HASHMAP_H__

#include <unordered_map>
#include <list>
#include <initializer_list>
#include <iterator>

namespace json_cpp { namespace inner { namespace utils {

template<
    typename Key, 
    typename Val, 
    typename Hash = std::hash<Key>,
    typename KeyEq = std::equal_to<Key>
>
class OrderedHashMap final {
private:
    using HashMap = std::unordered_map<Key, Val, Hash, KeyEq>;
    template<typename ItVal, typename Map> class Iterator;
public:
    using key_type = Key;
    using mapped_type = Val;
    using value_type = std::pair<Key const, Val>;
    using size_type = typename std::unordered_map<Key, Val, Hash, KeyEq>::size_type;
    using iterator = Iterator<value_type, HashMap>;
    using const_iterator = Iterator<value_type const, HashMap const>;

    OrderedHashMap() = default;
    OrderedHashMap(std::initializer_list<value_type> init)
        : map_(init)
    {
        for(auto &e: init) {
            order_.push_back(e.first);
        }
    }

    Val &operator[](Key const &key) {
        if(map_.find(key) == map_.end()) {
            order_.push_back(key);
        }
        return map_[key];
    }

    bool contains(Key const &key) const {
        return map_.find(key) != map_.end();
    }

    bool empty() const noexcept { return map_.empty(); }

    size_type size() const { return map_.size(); }

    void clear() noexcept { 
        map_.clear(); 
        order_.clear();
    }

    size_type erase(Key const &key) { 
        auto num_removed = map_.erase(key);
        if(2 * map_.size() < order_.size()) {
            shrink_to_fit();
        }
        return num_removed;
    }

    iterator begin() noexcept { return iterator(map_, order_.begin()); }
    iterator end() noexcept { return iterator(map_, order_.end()); }
    const_iterator begin() const noexcept { return const_iterator(map_, order_.begin()); }
    const_iterator end() const noexcept { return const_iterator(map_, order_.end()); }
    const_iterator cbegin() const noexcept { return const_iterator(map_, order_.begin()); }
    const_iterator cend() const noexcept { return const_iterator(map_, order_.end()); }

    // special members
    size_type shrink_to_fit() {
        if(map_.size() < order_.size()) {
            auto size_before = order_.size();
            order_.remove_if([this](Key &e) { 
                return map_.find(e) == map_.end(); 
            });
            return size_before - order_.size();
        }
        return 0;
    }
private:
    HashMap map_;
    std::list<Key> order_;

    template<typename ItVal, typename Map>
    class Iterator: public std::iterator<std::input_iterator_tag, ItVal> {
    public:
        using list_iterator = typename std::list<Key>::const_iterator;

        Iterator(Map &m, list_iterator const &pos)
            : map_(m)
            , pos_(pos)
        {}

        Iterator &operator++() {
            ++pos_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator ret = *this;
            ++pos_;
            return ret;
        }

        bool operator==(Iterator const &other) const noexcept {
            return pos_ == other.pos_ && &map_ == &other.map_;
        }

        bool operator!=(Iterator const &other) const noexcept { return !(*this == other); }
        
        ItVal &operator*() const { return *map_.find(*pos_); }
    private:
        Map &map_;
        list_iterator pos_;
    };
};

}}}

#endif