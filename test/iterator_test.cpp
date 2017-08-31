#include "gmock/gmock.h"

#include "sut/iterator"

#include <iterator>

using namespace testing;

namespace
{

using some_type = int;
some_type some_value = 53;

struct some_iterator
{
    using value_type = double;
    using difference_type = char;
    using pointer = long&;
    using reference = const char*;
    using iterator_category = sut::forward_iterator_tag;
};

struct container_mock
{
    MOCK_METHOD0(begin, some_type());
    MOCK_CONST_METHOD0(begin, some_type());

    MOCK_METHOD0(end, some_type());
    MOCK_CONST_METHOD0(end, some_type());
};

struct begin_end_test : Test
{
    container_mock mock;
    const container_mock const_mock;
    some_type array[16];
};

struct begin : begin_end_test {};
struct end : begin_end_test {};

}

TEST_F(begin, calls_begin_on_the_given_object_and_returns_its_value)
{
    EXPECT_CALL(mock, begin()).WillOnce(Return(some_value));
    auto begin = sut::begin(mock);

    ASSERT_THAT(begin, Eq(some_value));
}

TEST_F(begin, calls_const_begin_on_the_given_const_object_and_returns_its_value)
{
    EXPECT_CALL(const_mock, begin()).WillOnce(Return(some_value));
    auto begin = sut::begin(const_mock);

    ASSERT_THAT(begin, Eq(some_value));
}

TEST_F(begin, returns_the_address_of_the_given_array)
{
    auto begin = sut::begin(array);

    ASSERT_THAT(begin, Eq(array));
}

TEST_F(end, calls_end_on_the_given_object_and_returns_its_value)
{
    EXPECT_CALL(mock, end()).WillOnce(Return(some_value));
    auto end = sut::end(mock);

    ASSERT_THAT(end, Eq(some_value));
}

TEST_F(end, calls_const_end_on_the_given_const_object_and_returns_its_value)
{
    EXPECT_CALL(const_mock, end()).WillOnce(Return(some_value));
    auto end = sut::end(const_mock);

    ASSERT_THAT(end, Eq(some_value));
}

TEST_F(end, returns_the_address_of_the_given_array)
{
    auto end = sut::end(array);

    ASSERT_THAT(end, Eq(array + sizeof(array) / sizeof(array[0])));
}

TEST(iterator_traits, supports_pointers)
{
    using traits = sut::iterator_traits<some_type*>;

    StaticAssertTypeEq<traits::value_type, some_type>();
    StaticAssertTypeEq<traits::difference_type, sut::ptrdiff_t>();
    StaticAssertTypeEq<traits::pointer, some_type*>();
    StaticAssertTypeEq<traits::reference, some_type&>();
    StaticAssertTypeEq<traits::iterator_category,
                       sut::random_access_iterator_tag>();
}

TEST(iterator_traits, supports_const_pointers)
{
    using traits = sut::iterator_traits<const some_type*>;

    StaticAssertTypeEq<traits::value_type, some_type>();
    StaticAssertTypeEq<traits::difference_type, sut::ptrdiff_t>();
    StaticAssertTypeEq<traits::pointer, const some_type*>();
    StaticAssertTypeEq<traits::reference, const some_type&>();
    StaticAssertTypeEq<traits::iterator_category,
    sut::random_access_iterator_tag>();
}

TEST(iterator_traits, supports_iterators)
{
    using traits = sut::iterator_traits<some_iterator>;

    StaticAssertTypeEq<traits::value_type, some_iterator::value_type>();
    StaticAssertTypeEq<traits::difference_type, some_iterator::difference_type>();
    StaticAssertTypeEq<traits::pointer, some_iterator::pointer>();
    StaticAssertTypeEq<traits::reference, some_iterator::reference>();
    StaticAssertTypeEq<traits::iterator_category,
                       some_iterator::iterator_category>();
}
