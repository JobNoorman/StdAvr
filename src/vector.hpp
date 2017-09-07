#ifndef STDAVR_VECTOR_HPP
#define STDAVR_VECTOR_HPP

#include "namespace.hpp"
#include "utility.hpp"
#include "initializer_list.hpp"
#include "iterator.hpp"
#include "cstddef.hpp"
#include "cassert.hpp"
#include "cstdlib.hpp"

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

    vector(size_type count, const T& value) : vector(allocate_tag{}, count)
    {
        for (auto& element : *this)
            new (&element) T(value);
    }

    explicit vector(size_type count) : vector{allocate_tag{}, count}
    {
        for (auto& element : *this)
            new (&element) T();
    }

    vector(std::initializer_list<T> il) : vector(il.begin(), il.end())
    {
    }

    vector(vector&& other) noexcept : data_{other.data_}, size_{other.size_}
    {
        other.data_ = nullptr;
        other.size_ = 0;
    }

    template<typename InputIt,
             typename = detail::require_input_iterator<InputIt>>
    vector(InputIt first, InputIt last) : vector(allocate_tag{}, last - first)
    {
        auto it = first;

        for (auto& element : *this)
            new (&element) T(*it++);
    }

    ~vector()
    {
        delete[] data_;
    }

    vector& operator=(const vector& other)
    {
        auto copy = other;
        swap(copy);
        return *this;
    }

    // TODO Add noexcept
    vector& operator=(vector&& other)
    {
        swap(other);
        return *this;
    }

    vector& operator=(std::initializer_list<T> il)
    {
        auto vec = vector(il);
        swap(vec);
        return *this;
    }

    size_type size() const noexcept
    {
        return size_;
    }

    bool empty() const noexcept
    {
        return size() == 0;
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

    // TODO Add noexcept
    void swap(vector& other)
    {
        using STDAVR_NAMESPACE::swap;
        swap(data_, other.data_);
        swap(size_, other.size_);
        swap(capacity_, other.capacity_);
    }

    reference front()
    {
        return const_cast<reference>(const_cast<const vector*>(this)->front());
    }

    const_reference front() const
    {
        assert(!empty() && "front() called on empty vector");

        return data_[0];
    }

    reference back()
    {
        return const_cast<reference>(const_cast<const vector*>(this)->back());
    }

    const_reference back() const
    {
        assert(!empty() && "back() called on empty vector");

        return data_[size() - 1];
    }

    reference operator[](size_type pos)
    {
        return const_cast<reference>(const_cast<const vector&>(*this)[pos]);
    }

    const_reference operator[](size_type pos) const
    {
        assert(pos < size() && "operator[] index out of range");

        return data_[pos];
    }

    reference at(size_type pos)
    {
        return const_cast<reference>(const_cast<const vector*>(this)->at(pos));
    }

    const_reference at(size_type pos) const
    {
        if (pos >= size())
            abort();

        return (*this)[pos];
    }

    T* data() noexcept
    {
        return const_cast<T*>(const_cast<const vector*>(this)->data());
    }

    const T* data() const noexcept
    {
        return data_;
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

template<typename InputIt>
vector(InputIt, InputIt)
    -> vector<typename iterator_traits<InputIt>::value_type>;

template<class T>
void swap(vector<T>& lhs, vector<T>& rhs) noexcept(noexcept(lhs.swap(rhs)))
{
    lhs.swap(rhs);
}

}

#endif
