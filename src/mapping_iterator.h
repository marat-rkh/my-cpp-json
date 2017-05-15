#ifndef __MAPPING_ITERATOR_H__
#define __MAPPING_ITERATOR_H__

#include <functional>
#include <type_traits>

namespace json_cpp { namespace inner { namespace utils {

template<typename Iter, typename Val>
class MappingIterator: public std::iterator<
    std::input_iterator_tag,
    typename std::remove_reference<Val>::type,
    Val
> {
public:
    using input_type = typename Iter::reference;
    using result_type = Val;

    MappingIterator(Iter const &iter, nullptr_t np)
        : iter_(iter)
        , mapper_(np)
    {}

    template<typename Mapper>
    MappingIterator(Iter const &iter, Mapper mapper)
        : iter_(iter)
        , mapper_(mapper)
    {}

    MappingIterator &operator++() {
        ++iter_;
        return *this;
    }

    MappingIterator operator++(int) {
        MappingIterator ret = *this;
        ++iter_;
        return ret;
    }

    bool operator==(MappingIterator const &other) const noexcept {
        return iter_ == other.iter_;
    }

    bool operator!=(MappingIterator const &other) const noexcept {
        return !(*this == other);
    }

    result_type operator*() const { return mapper_(*iter_); }
private:
    Iter iter_;
    std::function<result_type(input_type)> mapper_;
};

template<typename Iter, typename Mapper>
auto MakeMappingBegin(Iter const &iter, Mapper mapper)
    -> MappingIterator<Iter, decltype(mapper(*iter))>
{
    return MappingIterator<Iter, decltype(mapper(*iter))>(iter, mapper);
}

template<typename Iter, typename Mapper>
auto MakeMappingEnd(Iter const &iter, Mapper mapper)
    -> MappingIterator<Iter, decltype(mapper(*iter))>
{
    return MappingIterator<Iter, decltype(mapper(*iter))>(iter, nullptr);
}

}}}

#endif