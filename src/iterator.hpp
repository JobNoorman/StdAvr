#ifndef STDAVR_ITERATOR_HPP
#define STDAVR_ITERATOR_HPP

#include "namespace.hpp"
#include "type_traits.hpp"
#include "cstddef.hpp"

namespace STDAVR_NAMESPACE
{

template<class C>
constexpr auto begin(C& c)
{
    return c.begin();
}

template<class C>
constexpr auto begin(const C& c)
{
    return c.begin();
}

template<class T, size_t N>
constexpr auto begin(T (&array)[N]) noexcept
{
    return array;
}

template<class C>
constexpr auto cbegin(const C& c) noexcept(noexcept(begin(c)))
{
    return begin(c);
}

template<class C>
constexpr auto end(C& c)
{
    return c.end();
}

template<class C>
constexpr auto end(const C& c)
{
    return c.end();
}

template<class T, size_t N>
constexpr auto end(T (&array)[N]) noexcept
{
    return array + N;
}

template<class C>
constexpr auto cend(const C& c) noexcept(noexcept(end(c)))
{
    return end(c);
}

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

namespace detail
{

template<typename Iterator, typename = void_t<>>
struct iterator_traits
{
};

template<typename Iterator>
struct iterator_traits<Iterator, void_t<typename Iterator::iterator_category,
                                        typename Iterator::value_type,
                                        typename Iterator::difference_type,
                                        typename Iterator::pointer,
                                        typename Iterator::reference>>
{
    using value_type        = typename Iterator::value_type;
    using difference_type   = typename Iterator::difference_type;
    using pointer           = typename Iterator::pointer;
    using reference         = typename Iterator::reference;
    using iterator_category = typename Iterator::iterator_category;
};

} // namespace detail

template<typename Iterator>
struct iterator_traits : detail::iterator_traits<Iterator>
{
};

template<typename T>
struct iterator_traits<T*>
{
    using value_type        = T;
    using difference_type   = ptrdiff_t;
    using pointer           = T*;
    using reference         = T&;
    using iterator_category = random_access_iterator_tag;
};

template<typename T>
struct iterator_traits<const T*>
{
    using value_type        = T;
    using difference_type   = ptrdiff_t;
    using pointer           = const T*;
    using reference         = const T&;
    using iterator_category = random_access_iterator_tag;
};

namespace detail
{

#define IS_X_ITERATOR(type)                                                 \
    template<typename T, typename = void>                                   \
    struct is_##type##_iterator : false_type {};                            \
    template<typename T>                                                    \
    struct is_##type##_iterator<                                            \
        T, enable_if_t<is_base_of_v<type##_iterator_tag,                    \
                                    typename T::iterator_category>>         \
    > : true_type {};                                                       \
    template<typename T>                                                    \
    constexpr inline bool is_##type##_iterator_v =                          \
        is_##type##_iterator<T>::value;                                     \
    template<typename T>                                                    \
    using require_##type##_iterator = enable_if_t<is_##type##_iterator_v<T>>

IS_X_ITERATOR(input);
IS_X_ITERATOR(output);
IS_X_ITERATOR(forward);
IS_X_ITERATOR(bidirectional);
IS_X_ITERATOR(random_access);

#undef IS_X_ITERATOR

}

}

#endif
