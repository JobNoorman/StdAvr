#ifndef STDAVR_VECTOR_HPP
#define STDAVR_VECTOR_HPP

#include "namespace.hpp"
#include "cstddef.hpp"

namespace STDAVR_NAMESPACE
{

template<typename T>
class vector
{
public:

    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = value_type*;
    using const_iterator = const value_type*;

    vector() : data_{nullptr}, size_{0}, capacity_{0}
    {
    }

    vector(const vector& other) : vector(allocate_tag{}, other.size())
    {
        auto other_it = other.begin();

        for (auto& element : *this)
            new (&element) T(*other_it++);
    }

    vector(size_type count, const T& value) : vector{allocate_tag{}, count}
    {
        for (auto& element : *this)
            new (&element) T(value);
    }

    explicit vector(size_type count) : vector{allocate_tag{}, count}
    {
        for (auto& element : *this)
            new (&element) T();
    }

    ~vector()
    {
        delete[] data_;
    }

    size_type size() const noexcept
    {
        return size_;
    }

    iterator begin() noexcept
    {
        return const_cast<iterator>(const_cast<const vector*>(this)->begin());
    }

    const_iterator begin() const noexcept
    {
        return data_;
    }

    const_iterator cbegin() const noexcept
    {
        return begin();
    }

    iterator end() noexcept
    {
        return const_cast<iterator>(const_cast<const vector*>(this)->end());
    }

    const_iterator end() const noexcept
    {
        return data_ + size_;
    }

    const_iterator cend() const noexcept
    {
        return end();
    }

private:

    struct allocate_tag{};

    vector(allocate_tag, size_t count)
    : data_{static_cast<value_type*>(
                ::operator new[](count * sizeof(value_type)))},
        size_{count}, capacity_{count}
    {
    }

    value_type* data_;
    size_type size_;
    size_type capacity_;
};

}

#endif
