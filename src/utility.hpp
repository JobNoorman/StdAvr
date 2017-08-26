#ifndef STDAVR_UTILITY_HPP
#define STDAVR_UTILITY_HPP

#include "namespace.hpp"
#include "type_traits.hpp"

namespace STDAVR_NAMESPACE
{

template<class T>
constexpr T&& forward(remove_reference_t<T>& t) noexcept
{
    return static_cast<T&&>(t);
}

template<class T>
constexpr T&& forward(remove_reference_t<T>&& t) noexcept
{
    return static_cast<T&&>(t);
}

template<class T>
constexpr remove_reference_t<T>&& move(T&& t) noexcept
{
    return static_cast<remove_reference_t<T>&&>(t);
}

template<typename T>
struct tuple_size;

template<typename T>
struct tuple_size<const T> : tuple_size<T> {};

template<typename T>
struct tuple_size<volatile T> : tuple_size<T> {};

template<typename T>
struct tuple_size<const volatile T> : tuple_size<T> {};

template<class T>
inline constexpr size_t tuple_size_v = tuple_size<T>::value;

}

#endif
