#include "gmock/gmock.h"

#include "sut/type_traits"

using namespace testing;

namespace
{

using some_type = int;
using some_type2 = double;

using some_integral_type = unsigned long;
constexpr some_integral_type some_integral_value = 4042;
constexpr bool some_bool_value = true;

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

TEST(integral_constant, has_the_given_type_as_value_type_member)
{
    using ic = sut::integral_constant<some_integral_type, some_integral_value>;

    StaticAssertTypeEq<ic::value_type, some_integral_type>();
    StaticAssertTypeEq<ic::type, ic>();
}

TEST(integral_constant, has_ist_own_type_as_type_member)
{
    using ic = sut::integral_constant<some_integral_type, some_integral_value>;

    StaticAssertTypeEq<ic::type, ic>();
}

TEST(integral_constant, has_the_given_value_as_value_member)
{
    using ic = sut::integral_constant<some_integral_type, some_integral_value>;

    ASSERT_THAT(ic::value, Eq(some_integral_value));
}

TEST(integral_constant, implicitly_converts_to_the_given_value)
{
    auto ic = sut::integral_constant<some_integral_type, some_integral_value>{};

    constexpr some_integral_type value = ic;

    static_assert(value == some_integral_value);
}

TEST(integral_constant, returns_the_given_value_when_called)
{
    auto ic = sut::integral_constant<some_integral_type, some_integral_value>{};

    constexpr some_integral_type value = ic();

    static_assert(value == some_integral_value);
}

TEST(bool_constant, is_an_integral_constant_with_type_bool)
{
    using bc = sut::bool_constant<some_bool_value>;

    StaticAssertTypeEq<bc::value_type, bool>();
}

TEST(true_type, has_value_true)
{
    using tt = sut::true_type;

    StaticAssertTypeEq<tt::value_type, bool>();
    static_assert(tt::value);
}

TEST(false_type, has_value_false)
{
    using ft = sut::false_type;

    StaticAssertTypeEq<ft::value_type, bool>();
    static_assert(!ft::value);
}
