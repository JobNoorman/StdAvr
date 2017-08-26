#include "gmock/gmock.h"

#include "sut/type_traits"

using namespace testing;

namespace
{

using some_type = int;

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
