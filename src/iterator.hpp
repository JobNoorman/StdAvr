#ifndef STDAVR_ITERATOR_HPP
#define STDAVR_ITERATOR_HPP

#include "namespace.hpp"
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

}

#endif
