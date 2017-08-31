#ifndef STDAVR_TYPE_TRAITS_HPP
#define STDAVR_TYPE_TRAITS_HPP

#include "namespace.hpp"

namespace STDAVR_NAMESPACE
{

template<class T, T V>
struct integral_constant
{
    using value_type = T;
    using type = integral_constant;

    static constexpr T value = V;

    constexpr operator value_type() const noexcept   {return value;}
    constexpr value_type operator()() const noexcept {return value;}
};

template<bool B>
using bool_constant = integral_constant<bool, B>;

using true_type  = bool_constant<true>;
using false_type = bool_constant<false>;

template<typename T> struct remove_reference      {using type = T;};
template<typename T> struct remove_reference<T&>  {using type = T;};
template<typename T> struct remove_reference<T&&> {using type = T;};

template<class T>
using remove_reference_t = typename remove_reference<T>::type;

template<typename...>
using void_t = void;

}

#endif
