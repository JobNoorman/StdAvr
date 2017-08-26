#include "gmock/gmock.h"

#include "sut/tuple"

#include <tuple>
#include <type_traits>

using namespace testing;

namespace
{

auto some_value1 = 1;
auto some_value2 = 'a';
int some_int1 = 42;
int some_int2 = 53;
auto some_tuple() {return sut::tuple{some_value1, some_value2};}

}

namespace std
{

// tuple_size and tuple_element must be declared in namespace std for structured
// bindings to work.
template<typename... Ts>
struct tuple_size<sut::tuple<Ts...>>
{
    static const auto value = sut::tuple_size<sut::tuple<Ts...>>::value;
};

template<std::size_t I, typename... Ts>
struct tuple_element<I, sut::tuple<Ts...>>
{
    using type = typename sut::tuple_element<I, sut::tuple<Ts...>>::type;
};

}

TEST(a_tuple, deduces_correct_types_from_constructor)
{
    using tup_type = decltype(sut::tuple(1, "foo"));

    StaticAssertTypeEq<tup_type, sut::tuple<int, const char*>>();
}

TEST(a_tuple, supports_structured_bindings)
{
    auto tup = sut::tuple(some_value1, some_value2);
    auto [value1, value2] = tup;

    ASSERT_THAT(value1, Eq(some_value1));
    ASSERT_THAT(value2, Eq(some_value2));
}

TEST(a_tuple, supports_structured_bindings_when_all_types_are_the_same)
{
    auto tup = sut::tuple(some_int1, some_int2);
    auto [value1, value2] = tup;

    ASSERT_THAT(value1, Eq(some_int1));
    ASSERT_THAT(value2, Eq(some_int2));
}

TEST(make_tuple, deduces_correct_types)
{
    using tup_type = decltype(sut::make_tuple(1, 'a'));

    StaticAssertTypeEq<tup_type, sut::tuple<int, char>>();
}

TEST(get_tuple, returns_correct_values)
{
    auto tup = sut::tuple(some_value1, some_value2);

    ASSERT_THAT(sut::get<0>(tup), Eq(some_value1));
    ASSERT_THAT(sut::get<1>(tup), Eq(some_value2));
}

TEST(get_tuple, returns_correct_values_when_all_types_are_the_same)
{
    auto tup = sut::tuple(some_int1, some_int2);

    ASSERT_THAT(sut::get<0>(tup), Eq(some_int1));
    ASSERT_THAT(sut::get<1>(tup), Eq(some_int2));
}

TEST(get_tuple, returns_a_non_const_lvalue_given_a_non_const_lvalue)
{
    auto tup = some_tuple();
    using get_type = decltype(sut::get<0>(tup));

    static_assert(std::is_lvalue_reference_v<get_type>);
    static_assert(!std::is_const_v<std::remove_reference_t<get_type>>);
}

TEST(get_tuple, returns_a_const_lvalue_given_a_const_lvalue)
{
    const auto tup = some_tuple();
    using get_type = decltype(sut::get<0>(tup));

    static_assert(std::is_lvalue_reference_v<get_type>);
    static_assert(std::is_const_v<std::remove_reference_t<get_type>>);
}

TEST(get_tuple, returns_an_rvalue_given_an_rvalue)
{
    using get_type = decltype(sut::get<0>(some_tuple()));

    static_assert(std::is_rvalue_reference_v<get_type>);
}

TEST(tuple_size_tuple, returns_correct_size)
{
    using tup_type = sut::tuple<int, char, int, const char*>;

    static_assert(sut::tuple_size_v<tup_type> == 4);
}

TEST(tuple_size_tuple, returns_correct_size_for_const_tuple)
{
    using tup_type = const sut::tuple<int, char, int, const char*>;

    static_assert(sut::tuple_size_v<tup_type> == 4);
}

TEST(tuple_size_tuple, returns_correct_size_for_volatile_tuple)
{
    using tup_type = volatile sut::tuple<int, char, int, const char*>;

    static_assert(sut::tuple_size_v<tup_type> == 4);
}

TEST(tuple_size_tuple, returns_correct_size_for_cv_tuple)
{
    using tup_type = const volatile sut::tuple<int, char, int, const char*>;

    static_assert(sut::tuple_size_v<tup_type> == 4);
}

TEST(tuple_element_tuple, returns_correct_types)
{
    using tup_type = sut::tuple<int, char>;

    StaticAssertTypeEq<sut::tuple_element_t<0, tup_type>, int>();
    StaticAssertTypeEq<sut::tuple_element_t<1, tup_type>, char>();
}
