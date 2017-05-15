#ifndef __ORDERED_HASHMAP_H__
#define __ORDERED_HASHMAP_H__

#include <unordered_map>
#include <list>
#include <initializer_list>
#include <iterator>
#include <functional>

#include "mapping_iterator.h"

namespace json_cpp { namespace inner { namespace utils {

/*
* Adapter for unordered_map with iterators traversing 
* map entries in the order they were inserted.
* 
* TODO Abstract over map type as the class does not use 
* any unordered_map specific operations
*/
template<
    typename Key, 
    typename Val, 
    typename Hash = std::hash<Key>,
    typename KeyEq = std::equal_to<Key>
>
class OrderedHashMap final {
private:
    using HashMap = std::unordered_map<Key, Val, Hash, KeyEq>;
    using KeyList = std::list<Key>;
public:
    using key_type = typename HashMap::key_type;
    using mapped_type = typename HashMap::mapped_type;
    using value_type = typename HashMap::value_type;
    using size_type = typename HashMap::size_type;
    using iterator = MappingIterator<typename KeyList::const_iterator, value_type &>;
    using const_iterator = MappingIterator<typename KeyList::const_iterator, value_type const &>;

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

    iterator begin() noexcept { return MakeMappingBegin(order_.cbegin(), EntryGetter()); }
    iterator end() noexcept { return MakeMappingEnd(order_.cend(), EntryGetter()); }
    const_iterator begin() const noexcept { return MakeMappingBegin(order_.begin(), EntryGetter()); }
    const_iterator end() const noexcept { return MakeMappingEnd(order_.end(), EntryGetter()); }
    const_iterator cbegin() const noexcept { return MakeMappingBegin(order_.begin(), EntryGetter()); }
    const_iterator cend() const noexcept { return MakeMappingEnd(order_.end(), EntryGetter()); }

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
    KeyList order_;

    std::function<value_type &(Key const&)> EntryGetter() {
        return [this](Key const &k)->value_type &{ return *map_.find(k); };
    }

    std::function<value_type const &(Key const&)> EntryGetter() const {
        return [this](Key const &k)->value_type const &{ return *map_.find(k); };
    }
};

}}}

#endif