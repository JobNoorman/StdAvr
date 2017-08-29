#include "gmock/gmock.h"

#include "sut/type_traits"

using namespace testing;

namespace
{

using some_type = int;
using some_type2 = double;

}

TEST(remove_reference, keeps_non_reference_type_intact)
{
    using type = some_type;
    using type_without_reference = sut::remove_reference_t<type>;

    StaticAssertTypeEq<type_without_reference, some_type>();
}

TEST(remove_reference, removes_lvalue_reference)
{
    using type = some_type&;
    using type_without_reference = sut::remove_reference_t<type>;

    StaticAssertTypeEq<type_without_reference, some_type>();
}

TEST(remove_reference, removes_rvalue_reference)
{
    using type = some_type&&;
    using type_without_reference = sut::remove_reference_t<type>;

    StaticAssertTypeEq<type_without_reference, some_type>();
}

TEST(remove_reference, removes_lvalue_reference_but_keeps_cv_intact)
{
    using base_type = const volatile some_type;
    using type = base_type&;
    using type_without_reference = sut::remove_reference_t<type>;

    StaticAssertTypeEq<type_without_reference, base_type>();
}

TEST(void_t, is_void_given_any_number_of_type_arguments)
{
    StaticAssertTypeEq<sut::void_t<>, void>();
    StaticAssertTypeEq<sut::void_t<some_type>, void>();
    StaticAssertTypeEq<sut::void_t<some_type, some_type2>, void>();
}
