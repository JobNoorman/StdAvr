#include "gmock/gmock.h"

#include "sut/vector"

using namespace testing;

namespace
{

using some_type = int;

const sut::size_t some_size = 5;
const some_type some_value = 42;
auto some_initializer_list = {2, 5, 1, 7, 5};

}

TEST(a_vector, has_size_zero_when_default_constructed)
{
    auto vec = sut::vector<some_type>();

    ASSERT_THAT(vec.size(), Eq(0u));
}

TEST(a_vector, has_the_given_size_when_constructed)
{
    auto vec = sut::vector<some_type>(some_size, some_value);

    ASSERT_THAT(vec.size(), Eq(some_size));
}

TEST(a_vector, contains_count_elements_equal_to_the_given_value)
{
    auto vec = sut::vector<some_type>(3, some_value);

    ASSERT_THAT(vec, ElementsAreArray({some_value, some_value, some_value}));
}

TEST(a_vector, contains_count_default_constructed_elements_when_no_value_given)
{
    auto vec = sut::vector<some_type>(3);

    ASSERT_THAT(vec, ElementsAreArray({some_type{}, some_type{}, some_type{}}));
}



TEST(a_vector, has_the_same_elements_as_the_source_vector_it_was_copied_from)
{
    auto source_vec = sut::vector(some_size, some_value);

    auto vec = sut::vector(source_vec);

    ASSERT_THAT(vec, ElementsAreArray(source_vec));
}

TEST(a_vector, is_empty_when_it_has_no_elements)
{
    auto vec = sut::vector<some_type>();

    ASSERT_TRUE(vec.empty());
}

TEST(a_vector, contains_the_element_from_the_given_initializer_list)
{
    auto vec = sut::vector<some_type>(some_initializer_list);

    ASSERT_THAT(vec, ElementsAreArray(some_initializer_list));
}

TEST(a_vector, has_the_same_elements_as_the_source_vector_it_was_moved_from)
{
    auto source_vec = sut::vector(some_initializer_list);
    auto source_copy = source_vec;

    auto vec = sut::vector(std::move(source_vec));

    ASSERT_THAT(vec, ElementsAreArray(source_copy));
}

TEST(a_vector, is_empty_after_being_moved_from)
{
    auto source_vec = sut::vector(some_initializer_list);

    sut::vector(std::move(source_vec));

    ASSERT_TRUE(source_vec.empty());
}
