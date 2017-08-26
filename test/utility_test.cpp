#include "gmock/gmock.h"

#include "sut/utility"

#include <type_traits>

using namespace testing;

namespace
{

using some_type = int;
some_type some_lvalue = 42;
some_type some_rvalue() {return 42;}

}

TEST(move, returns_an_rvalue_reference_given_an_lvalue)
{
    using moved_type = decltype(sut::move(some_lvalue));

    static_assert(std::is_rvalue_reference_v<moved_type>);
}

TEST(move, returns_an_rvalue_reference_given_an_rvalue)
{
    using moved_type = decltype(sut::move(some_rvalue()));

    static_assert(std::is_rvalue_reference_v<moved_type>);
}

TEST(forward, returns_an_lvalue_reference_given_an_lvalue_reference)
{
    using forwarded_type = decltype(sut::forward<some_type&>(some_lvalue));

    static_assert(std::is_lvalue_reference_v<forwarded_type>);
}

TEST(forward, returns_an_rvalue_reference_given_an_rvalue_reference)
{
    using forwarded_type = decltype(sut::forward<some_type>(some_rvalue()));

    static_assert(std::is_rvalue_reference_v<forwarded_type>);
}
