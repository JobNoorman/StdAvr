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

struct some_class_type {};
union some_union_type {};
enum some_enum_type {};
enum class some_enum_class_type {};

struct some_non_trivial_type {some_non_trivial_type() {}};
struct some_non_standard_layout_type {int i; private: int j;};

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

TEST(is_union, is_true_for_unions)
{
    static_assert(sut::is_union_v<some_union_type>);
}

TEST(is_union, is_false_for_classes)
{
    static_assert(!sut::is_union_v<some_class_type>);
}

TEST(is_union, is_false_for_integrals)
{
    static_assert(!sut::is_union_v<some_integral_type>);
}

TEST(is_class, is_true_for_classes)
{
    static_assert(sut::is_class_v<some_class_type>);
}

TEST(is_class, is_false_for_unions)
{
    static_assert(!sut::is_class_v<some_union_type>);
}

TEST(is_class, is_false_for_integrals)
{
    static_assert(!sut::is_class_v<some_integral_type>);
}

TEST(is_enum, is_true_for_enums)
{
    static_assert(sut::is_enum_v<some_enum_type>);
}

TEST(is_enum, is_true_for_enum_classes)
{
    static_assert(sut::is_enum_v<some_enum_class_type>);
}

TEST(is_enum, is_false_for_unions)
{
    static_assert(!sut::is_enum_v<some_union_type>);
}

TEST(is_enum, is_false_for_classes)
{
    static_assert(!sut::is_enum_v<some_class_type>);
}

TEST(is_enum, is_false_for_integrals)
{
    static_assert(!sut::is_enum_v<some_integral_type>);
}

TEST(is_standard_layout, is_true_for_integral_types)
{
    static_assert(sut::is_standard_layout_v<some_integral_type>);
}

TEST(is_standard_layout, is_true_for_class_types_with_uniform_access_members)
{
    class some_class_type {int i;};

    static_assert(sut::is_standard_layout_v<some_class_type>);
}

TEST(is_standard_layout, is_false_for_class_types_with_mixed_access_members)
{

    class some_class_type {int i; public: int j;};

    static_assert(!sut::is_standard_layout_v<some_class_type>);
}

TEST(is_standard_layout, is_false_for_class_types_with_virtual_functions)
{

    class some_class_type {virtual void f() {}};

    static_assert(!sut::is_standard_layout_v<some_class_type>);
}

TEST(is_standard_layout, is_false_for_class_types_with_virtual_bases)
{
    struct some_base_type {};
    struct some_class_type : virtual some_base_type {};

    static_assert(!sut::is_standard_layout_v<some_class_type>);
}

TEST(is_abstract, is_true_for_class_types_with_pure_virtual_functions)
{
    struct some_class_type {virtual void f() = 0;};

    static_assert(sut::is_abstract_v<some_class_type>);
}

TEST(is_abstract, is_true_for_class_types_with_inherited_pure_virtual_functions)
{
    struct some_base_type {virtual void f() = 0;};
    struct some_class_type : some_base_type {};

    static_assert(sut::is_abstract_v<some_class_type>);
}

TEST(is_abstract, is_false_for_class_types_without_any_pure_virtual_functions)
{
    struct some_class_type {virtual void f() {}};

    static_assert(!sut::is_abstract_v<some_class_type>);
}

TEST(is_abstract, is_false_for_union_types)
{
    static_assert(!sut::is_abstract_v<some_union_type>);
}

TEST(is_abstract, is_false_for_integral_types)
{
    static_assert(!sut::is_abstract_v<some_integral_type>);
}

TEST(is_empty, is_true_for_class_types_without_members_or_virtual_functions)
{
    struct some_class_type {};

    static_assert(sut::is_empty_v<some_class_type>);
}

TEST(is_empty, is_false_for_class_types_with_non_static_members)
{
    struct some_class_type {int i;};

    static_assert(!sut::is_empty_v<some_class_type>);
}

TEST(is_empty, is_false_for_class_types_with_virtual_functions)
{
    struct some_class_type {virtual void f() {}};

    static_assert(!sut::is_empty_v<some_class_type>);
}

TEST(is_empty, is_false_for_union_types)
{
    static_assert(!sut::is_empty_v<some_union_type>);
}

TEST(is_empty, is_false_for_integral_types)
{
    static_assert(!sut::is_empty_v<some_integral_type>);
}

TEST(is_trivial, is_true_for_trivial_class_types)
{
    struct some_class_type {};

    static_assert(sut::is_trivial_v<some_class_type>);
}

TEST(is_trivial, is_true_for_integral_types)
{
    static_assert(sut::is_trivial_v<some_integral_type>);
}

TEST(is_trivial, is_false_for_class_types_with_non_default_default_constructor)
{
    struct some_class_type {some_class_type() {}};

    static_assert(!sut::is_trivial_v<some_class_type>);
}

TEST(is_trivial, is_false_for_class_types_with_non_default_copy_constructor)
{
    struct some_class_type {some_class_type(const some_class_type&) {}};

    static_assert(!sut::is_trivial_v<some_class_type>);
}

TEST(is_trivial, is_false_for_class_types_with_virtual_functions)
{
    struct some_class_type {virtual void f() {}};

    static_assert(!sut::is_trivial_v<some_class_type>);
}

TEST(is_trivial, is_false_for_class_types_with_non_trivial_non_static_members)
{
    struct some_non_trivial_class_type {virtual void f() {}};
    struct some_class_type {some_non_trivial_class_type m;};

    static_assert(!sut::is_trivial_v<some_class_type>);
}

TEST(is_pod, is_true_for_integral_types)
{
    static_assert(sut::is_pod_v<some_integral_type>);
}

TEST(is_pod, is_true_for_class_types_that_are_trivial_and_standard_layout)
{
    struct some_class_type {some_integral_type m;};

    static_assert(sut::is_pod_v<some_class_type>);
}

TEST(is_pod, is_false_for_non_trivial_types)
{
    static_assert(!sut::is_pod_v<some_non_trivial_type>);
}

TEST(is_pod, is_false_for_non_standard_layout_types)
{
    static_assert(!sut::is_pod_v<some_non_standard_layout_type>);
}

TEST(is_polymorphic, is_true_for_class_types_with_virtual_functions)
{
    struct some_class_type {virtual void f() {}};

    static_assert(sut::is_polymorphic_v<some_class_type>);
}

TEST(is_polymorphic, is_true_for_class_types_with_inherited_virtual_functions)
{
    struct some_base_class_type {virtual void f() {}};
    struct some_class_type : some_base_class_type {};

    static_assert(sut::is_polymorphic_v<some_class_type>);
}

TEST(is_polymorphic, is_false_for_class_types_without_virtual_functions)
{
    struct some_class_type {};

    static_assert(!sut::is_polymorphic_v<some_class_type>);
}

TEST(is_base_of, is_true_for_a_class_and_a_subclass)
{
    struct some_subclass_type : some_class_type {};

    static_assert(sut::is_base_of_v<some_class_type, some_subclass_type>);
}

TEST(is_base_of, is_true_for_a_class_and_itself)
{
    static_assert(sut::is_base_of_v<some_class_type, some_class_type>);
}

TEST(is_base_of, is_false_for_union_types)
{
    static_assert(!sut::is_base_of_v<some_union_type, some_union_type>);
}

TEST(is_base_of, is_false_for_integral_types)
{
    static_assert(!sut::is_base_of_v<some_integral_type, some_integral_type>);
}
