#ifndef STDAVR_TYPE_TRAITS_HPP
#define STDAVR_TYPE_TRAITS_HPP

#include "namespace.hpp"

namespace STDAVR_NAMESPACE
{

template<typename T> struct remove_reference      {using type = T;};
template<typename T> struct remove_reference<T&>  {using type = T;};
template<typename T> struct remove_reference<T&&> {using type = T;};

template<class T>
using remove_reference_t = typename remove_reference<T>::type;

template<typename...>
using void_t = void;

}

#endif
