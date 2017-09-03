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

#define INTRINSIC_TRAIT(name)                                           \
    template<typename T> struct name : bool_constant<__##name(T)> {};   \
    template<typename T> inline constexpr bool name##_v = name<T>::value

INTRINSIC_TRAIT(is_union);
INTRINSIC_TRAIT(is_class);
INTRINSIC_TRAIT(is_enum);
INTRINSIC_TRAIT(is_abstract);
INTRINSIC_TRAIT(is_polymorphic);
INTRINSIC_TRAIT(is_empty);
INTRINSIC_TRAIT(is_standard_layout);
INTRINSIC_TRAIT(is_trivial);
INTRINSIC_TRAIT(is_pod);

#undef INTRINSIC_TRAIT

template<class Base, class Derived>
struct is_base_of : bool_constant<__is_base_of(Base, Derived)> {};

template<class Base, class Derived>
inline constexpr bool is_base_of_v = is_base_of<Base, Derived>::value;

template<typename T> struct remove_reference      {using type = T;};
template<typename T> struct remove_reference<T&>  {using type = T;};
template<typename T> struct remove_reference<T&&> {using type = T;};

template<class T>
using remove_reference_t = typename remove_reference<T>::type;

template<typename...>
using void_t = void;

}

#endif
