#include "gmock/gmock.h"

#include "sut/vector"

using namespace testing;

namespace
{

using some_type = int;

const sut::size_t some_size = 5;
const some_type some_value = 42;
auto some_initializer_list = {2, 5, 1, 7, 5};
auto some_vec1 = sut::vector{2, 4, 3, 8};
auto some_vec1_index = decltype(some_vec1)::size_type{2};
auto some_vec2 = sut::vector{4, 2, 5, 6, 9, 0};
const auto some_const_vec = sut::vector{4lu, 2lu, 5lu, 6lu, 9lu, 0lu};
auto some_const_vec_index = decltype(some_const_vec)::size_type{4};

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

TEST(a_vector, has_the_same_elements_as_the_source_vector_it_was_assigned_from)
{
    auto source_vec = sut::vector(some_initializer_list);

    decltype(source_vec) vec;
    vec = source_vec;

    ASSERT_THAT(vec, ElementsAreArray(source_vec));
}

TEST(a_vector, has_the_same_elements_as_the_source_vector_it_was_move_assigned_from)
{
    auto source_vec = sut::vector(some_initializer_list);
    auto source_copy = source_vec;

    decltype(source_vec) vec;
    vec = std::move(source_vec);

    ASSERT_THAT(vec, ElementsAreArray(source_copy));
}

TEST(a_vector, has_the_same_elements_as_the_source_initializer_list_it_was_assigned_from)
{
    auto source_vec = sut::vector(some_initializer_list);
    auto source_copy = source_vec;

    decltype(sut::vector(some_initializer_list)) vec;
    vec = some_initializer_list;

    ASSERT_THAT(vec, ElementsAreArray(some_initializer_list));
}

TEST(a_vector, has_the_same_elements_as_the_other_vector_after_swap)
{
    auto vec1 = some_vec1;
    auto vec2 = some_vec2;

    vec1.swap(vec2);

    ASSERT_THAT(vec1, ElementsAreArray(some_vec2));
    ASSERT_THAT(vec2, ElementsAreArray(some_vec1));
}

TEST(a_vector, has_the_same_elements_as_the_other_vector_after_std_swap)
{
    auto vec1 = some_vec1;
    auto vec2 = some_vec2;

    sut::swap(vec1, vec2);

    ASSERT_THAT(vec1, ElementsAreArray(some_vec2));
    ASSERT_THAT(vec2, ElementsAreArray(some_vec1));
}

TEST(a_vector, contains_the_elements_from_the_given_iterator_range)
{
    auto vec = sut::vector(some_vec1.begin(), some_vec1.end());

    ASSERT_THAT(vec, ElementsAreArray(some_vec1));
}

TEST(a_vector, returns_first_element_for_front)
{
    auto front = some_vec1.front();

    ASSERT_THAT(front, Eq(*some_vec1.begin()));
}

TEST(a_vector, returns_first_element_for_const_front)
{
    auto front = some_const_vec.front();

    ASSERT_THAT(front, Eq(*some_const_vec.begin()));
}

TEST(a_vector, returns_last_element_for_back)
{
    auto back = some_vec1.back();

    ASSERT_THAT(back, Eq(*(some_vec1.end() - 1)));
}

TEST(a_vector, returns_last_element_for_const_back)
{
    auto back = some_const_vec.back();

    ASSERT_THAT(back, Eq(*(some_const_vec.end() - 1)));
}

TEST(a_vector, returns_the_element_at_the_given_index_for_for_array_access)
{
    auto element = some_vec1[some_vec1_index];

    ASSERT_THAT(element, Eq(*(some_vec1.begin() + some_vec1_index)));
}

TEST(a_vector, returns_the_element_at_the_given_index_for_for_const_array_access)
{
    auto element = some_const_vec[some_const_vec_index];

    ASSERT_THAT(element, Eq(*(some_const_vec.begin() + some_const_vec_index)));
}

TEST(a_vector, returns_the_element_at_the_given_index_for_for_at)
{
    auto element = some_vec1.at(some_vec1_index);

    ASSERT_THAT(element, Eq(*(some_vec1.begin() + some_vec1_index)));
}

TEST(a_vector, returns_the_element_at_the_given_index_for_for_const_at)
{
    auto element = some_const_vec.at(some_const_vec_index);

    ASSERT_THAT(element, Eq(*(some_const_vec.begin() + some_const_vec_index)));
}

TEST(a_vector, returns_a_pointer_to_an_array_containing_all_element_for_data)
{
    auto data = some_vec1.data();
    auto data_vec = sut::vector(data, data + some_vec1.size());

    ASSERT_THAT(data_vec, ElementsAreArray(some_vec1));
}

TEST(a_vector, returns_a_pointer_to_an_array_containing_all_element_for_const_data)
{
    auto data = some_const_vec.data();
    auto data_vec = sut::vector(data, data + some_const_vec.size());

    ASSERT_THAT(data_vec, ElementsAreArray(some_const_vec));
}
