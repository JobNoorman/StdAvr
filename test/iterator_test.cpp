#include "gmock/gmock.h"

#include "sut/iterator"

#include <iterator>

using namespace testing;

namespace
{

using some_type = int;
some_type some_value = 53;

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
