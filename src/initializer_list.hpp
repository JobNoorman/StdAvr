#ifndef STDAVR_INITIALIZER_LIST_HPP
#define STDAVR_INITIALIZER_LIST_HPP

#include "namespace.hpp"
#include "cstddef.hpp"

namespace STDAVR_NAMESPACE
{

template<typename T>
class initializer_list
{
public:

    using value_type = T;
    using size_type = size_t;
    using reference = const value_type&;
    using const_reference = const value_type&;
    using iterator = const value_type*;
    using const_iterator = const value_type*;

    constexpr initializer_list() noexcept : data_{nullptr}, size_{0}
    {
    }

    constexpr size_type size() const noexcept
    {
        return size_;
    }

    bool empty() const noexcept
    {
        return size() == 0;
    }

    constexpr const_iterator begin() const noexcept
    {
        return data_;
    }

    constexpr const_iterator end() const noexcept
    {
        return data_ + size_;
    }

private:

    // The compiler automatically initializes an std::initializer_list if it has
    // the following two members in this order.
    value_type* data_;
    size_type size_;
};

template<class E>
constexpr const E* begin(initializer_list<E> il) noexcept
{
    return il.begin();
}

template<class E>
constexpr const E* end(initializer_list<E> il) noexcept
{
    return il.end();
}

}

#endif
