#ifndef STDAVR_TUPLE_HPP
#define STDAVR_TUPLE_HPP

#include "namespace.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#include "cstddef.hpp"

namespace STDAVR_NAMESPACE
{

namespace detail
{

template<size_t I, typename Tuple>
constexpr auto&& get(Tuple&&) noexcept;

} // namespace detail

template<typename... Types>
class tuple;

template<typename Head, typename... Tail>
class tuple<Head, Tail...> : public tuple<Tail...>
{
public:

    tuple(const Head& value, const Tail&... rest)
        : tuple<Tail...>{rest...}, value_{value}
    {
    }

private:

    template<size_t I, typename Tuple>
    friend constexpr auto&& detail::get(Tuple&&) noexcept;

    Head value_;
};

template<typename... Ts>
tuple(Ts...) -> tuple<Ts...>;

template<>
class tuple<> {};

template<typename... Ts>
auto make_tuple(Ts&&... values)
{
    return tuple<Ts...>{forward<Ts>(values)...};
}

template<typename... Ts>
struct tuple_size<tuple<Ts...>>
{
    static const size_t value = sizeof...(Ts);
};

template<size_t I, typename T>
struct tuple_element;

template<size_t I, typename T0, typename... Rest>
struct tuple_element<I, tuple<T0, Rest...>>
{
    using type = typename tuple_element<I - 1, tuple<Rest...>>::type;
};

template<typename Head, typename... Tail>
struct tuple_element<0, tuple<Head, Tail...>>
{
    using type = Head;
};

template<size_t I, class T>
using tuple_element_t = typename tuple_element<I, T>::type;

namespace detail
{

template<typename T>
struct tuple_parent;

template<typename Head, typename... Tail>
struct tuple_parent<tuple<Head, Tail...>>
{
    using type = tuple<Tail...>;
};

template<typename T>
struct tuple_parent<T&>
{
    using type = typename tuple_parent<T>::type&;
};

template<typename T>
struct tuple_parent<T&&>
{
    using type = typename tuple_parent<T>::type&&;
};

template<typename T>
using tuple_parent_t = typename tuple_parent<T>::type;

template<size_t I, typename Tuple>
constexpr auto&& get(Tuple&& tup) noexcept
{
    using tuple_type = remove_reference_t<Tuple>;
    static_assert(I < tuple_size_v<tuple_type>, "tuple index out of range");

    if constexpr (I == 0)
        return forward<Tuple>(tup).value_;
    else
        return get<I - 1>(forward<tuple_parent_t<Tuple>>(tup));
}

} // namespace detail

template<size_t I, typename Head, typename... Tail>
constexpr auto& get(tuple<Head, Tail...>& tup) noexcept
{
    return detail::get<I>(tup);
}

template<size_t I, typename Head, typename... Tail>
constexpr auto& get(const tuple<Head, Tail...>& tup) noexcept
{
    return detail::get<I>(tup);
}

template<size_t I, typename Head, typename... Tail>
constexpr auto&& get(tuple<Head, Tail...>&& tup) noexcept
{
    return detail::get<I>(move(tup));
}

} // namespace STDAVR_NAMESPACE

#endif
