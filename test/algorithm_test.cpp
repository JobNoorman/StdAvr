#include "gmock/gmock.h"

#include "sut/algorithm"

#include <iterator>

using namespace testing;

namespace
{

using some_type = int;

some_type some_array[] = {1, 4, 3, 7, 9};

}

TEST(copy, copies_elements)
{
    some_type array[sizeof(some_array) / sizeof(some_array[0])];

    sut::copy(std::begin(some_array), std::end(some_array), std::begin(array));

    ASSERT_THAT(array, ElementsAreArray(some_array));
}

TEST(copy, returns_end_of_output_iterator)
{
    some_type array[sizeof(some_array) / sizeof(some_array[0])];

    auto out_end = sut::copy(std::begin(some_array), std::end(some_array),
                             std::begin(array));

    ASSERT_THAT(out_end, Eq(std::end(array)));
}
