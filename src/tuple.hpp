#ifndef STDCPPAVR_TUPLE_HPP
#define STDCPPAVR_TUPLE_HPP

#include <stddef.h>

namespace std
{

namespace detail
{

template<size_t N, typename... Ts>
struct tuple_get;

} // namespace  detail

template<typename... Types>
class tuple;

template<typename T, typename... Rest>
class tuple<T, Rest...> : public tuple<Rest...>
{
public:

    tuple(T value, Rest... rest) : tuple<Rest...>{rest...}, value_{value}
    {
    }

private:

    template<size_t I, typename... Ts>
    friend struct detail::tuple_get;

    T value_;
};

template<typename... Ts>
tuple(Ts...) -> tuple<Ts...>;

template<>
class tuple<> {};

template<typename... Ts>
auto make_tuple(Ts... values)
{
    return tuple<Ts...>{values...};
}

template<typename T>
struct tuple_size;

template<typename... Ts>
struct tuple_size<tuple<Ts...>>
{
    static const size_t value = sizeof...(Ts);
};

namespace detail
{

template<size_t N, typename T0, typename... Rest>
struct tuple_get<N, T0, Rest...>
{
    static_assert(N < sizeof...(Rest) + 1, "tuple index out of range");

    static auto get(const tuple<T0, Rest...>& tup)
    {
        return tuple_get<N - 1, Rest...>::get(tup);
    }
};

template<typename T0, typename... Rest>
struct tuple_get<0, T0, Rest...>
{
    static auto get(const tuple<T0, Rest...>& tup)
    {
        return tup.value_;
    }
};

} // namespace detail

template<size_t N, typename T0, typename... Rest>
auto get(const tuple<T0, Rest...>& tup)
{
    return detail::tuple_get<N, T0, Rest...>::get(tup);
}

template<size_t I, typename T>
struct tuple_element;

template<size_t I, typename T0, typename... Rest>
struct tuple_element<I, tuple<T0, Rest...>>
{
    using type = typename tuple_element<I - 1, tuple<Rest...>>::type;
};

template<typename T0, typename... Rest>
struct tuple_element<0, tuple<T0, Rest...>>
{
    using type = T0;
};

}

#endif
