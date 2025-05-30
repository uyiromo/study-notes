#include "gtest/gtest.h"
#include <initializer_list>
#include <optional>
#include <utility>
#include <vector>

namespace
{
struct Sx
{
    explicit Sx(bool&&) {}; // NOLINT
};

struct Smv
{
    Smv(const Smv&) = delete;
    auto operator=(const Smv&) -> Smv& = delete;
    auto operator=(Smv&&) -> Smv& = delete;

    Smv() = default;
    Smv(Smv&&) = default;
    ~Smv() = default;
};

struct Scp
{
    Scp(Scp&&) = delete;
    auto operator=(const Scp&) -> Scp& = delete;
    auto operator=(Scp&&) -> Scp& = delete;

    Scp() = default;
    Scp(const Scp&) = default;
    ~Scp() = default;
};

struct Smv2
{
    Smv2(const Smv2&) = delete;
    auto operator=(const Smv2&) -> Smv2& = delete;

    Smv2() = default;
    Smv2(Smv2&&) = default;
    auto operator=(Smv2&&) -> Smv2& = default;
    ~Smv2() = default;
};

struct Scp2
{
    Scp2(Scp2&&) = delete;
    auto operator=(Scp2&&) -> Scp2& = delete;

    Scp2() = default;
    Scp2(const Scp2&) = default;
    auto operator=(const Scp2&) -> Scp2& = default;
    ~Scp2() = default;
};

TEST(
    optional, Constructor
)
{
    using T = bool;

    // (1) (2)
    // 値を持たない
    auto opt1 = std::optional<T>();
    auto opt2 = std::optional<T>(std::nullopt);
    static_assert(std::is_same_v<T, typename decltype(opt1)::value_type>);
    static_assert(std::is_same_v<T, typename decltype(opt2)::value_type>);

    EXPECT_FALSE(opt1.has_value());
    EXPECT_FALSE(opt2.has_value());

    // (3) (4)
    // copy/move
    auto optX = std::optional<T>(true); // NOLINT
    auto opt3(std::as_const(optX));
    auto opt4(std::move(optX));         // NOLINT
    static_assert(std::is_same_v<T, typename decltype(opt3)::value_type>);
    static_assert(std::is_same_v<T, typename decltype(opt4)::value_type>);
    EXPECT_TRUE(opt3.has_value());
    EXPECT_TRUE(opt4.has_value());

    // (5) (6) constructible
    std::optional<Sx> opt5(Sx(true)); // NOLINT
    static_assert(std::is_same_v<Sx, typename decltype(opt5)::value_type>);
    EXPECT_TRUE(opt5.has_value());

    // (7)
    // 複数の引数を Forward して construct
    // std::inplace は overload resolution のための tag
    auto opt6 = std::optional<std::tuple<bool, char>>(std::in_place, true,
                                                      'v'); // NOLINT

    // (8)
    // 複数の引数を Forward して construct
    // std::inplace は overload resolution のための tag
    auto opt7 = std::optional<std::tuple<std::vector<int>, bool>>(
        std::in_place,
        std::initializer_list<int>{1, 2, 3},
        true
    ); // NOLINT

    // 値から直接構築する場合、明示しない限り CV は剥がされる
    /*
        template <class U = std::remove_cv_t<T>>
        constexpr optional(U && value);
    */
    constexpr T b1 = true; // NOLINT

    // T
    auto opt8 = std::optional(b1);
    static_assert(std::is_same_v<T, typename decltype(opt8)::value_type>);

    // const T
    auto opt9 = std::optional<const T>(b1);
    static_assert(std::is_same_v<const T, typename decltype(opt9)::value_type>);
}

TEST(
    optional, Constructor2
)
{
    std::optional<Smv> opt1;
    std::optional<Scp> opt2;

    // CopyCtor する場合、中身の型も CopyCtor される
    // auto opt3(opt1);
    auto opt4(opt2);

    // MoveCtor する場合、中身の型も MoveCtor される
    auto opt5(std::move(opt1));
    auto opt6(std::move(opt2)); // NOLINT

    // CopyAssign する場合、中身の型も CopyAssign される
    // auto opt7 = opt1;
    auto opt8 = opt2;

    // MoveAssign する場合、中身の型も MoveAssign される
    auto opt9 = std::move(opt1);
    auto opt10 = std::move(opt2); // NOLINT
}

TEST(
    optional, Observers
)
{
    auto opt1 = std::optional<int>(42); // NOLINT
    auto opt2 = std::optional<int>();   // NOLINT

    // operator-> は pointer
    // operator* は reference
    auto* ret1 = opt1.operator->();
    static_assert(std::is_same_v<decltype(ret1), int*>);

    auto& ret2 = opt1.operator*();
    static_assert(std::is_same_v<decltype(ret2), int&>);

    auto&& ret3 = std::move(opt1).operator*();
    static_assert(std::is_same_v<decltype(ret3), int&&>);

    // bool()
    // has_value()
    EXPECT_TRUE(opt1.has_value());
    EXPECT_FALSE(opt2);

    // value()
    static_assert(std::is_same_v<decltype(opt1.value()), int&>);
    static_assert(std::is_same_v<decltype(std::move(opt1).value()), int&&>);
    EXPECT_THROW(opt2.value(), std::bad_optional_access);

    // value_or()
    EXPECT_EQ(opt1.value_or(0), 42);
    EXPECT_EQ(opt2.value_or(-1), -1);

    // value_or() は、`T` と `U` が異なっていても良い
    EXPECT_EQ(opt2.value_or(true), true);
    EXPECT_EQ(opt2.value_or(-1.0), -1.0);
}

TEST(
    optional, Monadic
)
{
    auto opt1 = std::optional<int>(42); // NOLINT
    auto opt2 = std::optional<int>();   // NOLINT

    auto fn1 = [](int __x) -> std::optional<double> { return std::make_optional(__x * 1.0); };

    auto fn2 = [](int __x) -> double { return __x * 1.0; };

    auto fn3 = []() -> double { return 1.0; };
    auto fn4 = []() -> int { return 1; };
    auto fn5 = []() -> std::optional<int> { return std::make_optional(1); };

    // and_then
    // auto ret1 = opt1.and_then(fn2); // ill-formed
    auto ret1 = opt1.and_then(fn1);
    auto ret2 = opt2.and_then(fn1);
    static_assert(std::is_same_v<decltype(ret1), std::optional<double>>);
    static_assert(std::is_same_v<decltype(ret2), std::optional<double>>);
    EXPECT_TRUE(ret1);
    EXPECT_TRUE(!ret2);

    // transform
    // 返り値の型は std::remove_cv_t<std::invoke_result_t<F, (const) T&>>
    auto ret3 = opt1.transform(fn2);
    auto ret4 = opt2.transform(fn2);
    static_assert(std::is_same_v<decltype(ret3), std::optional<double>>);
    static_assert(std::is_same_v<decltype(ret4), std::optional<double>>);
    EXPECT_TRUE(ret3);
    EXPECT_TRUE(!ret4);

    // or_else
    // auto ret5 = opt1.or_else(fn3); // std::remove_cv_t<std::invoke_result_t<F>> = double
    // auto ret5 = opt1.or_else(fn4); // std::remove_cv_t<std::invoke_result_t<F>> = int
    auto ret5 = opt1.or_else(fn5);
    auto ret6 = opt2.or_else(fn5);
    static_assert(std::is_same_v<decltype(ret5), std::optional<int>>);
    static_assert(std::is_same_v<decltype(ret6), std::optional<int>>);
    EXPECT_TRUE(ret5);
    EXPECT_TRUE(ret6);
}

TEST(
    optional, Modifiers
)
{
    auto opt1 = std::optional<int>(42);              // NOLINT
    auto opt2 = std::optional<int>(12);              // NOLINT
    auto opt3 = std::optional<int>();                // NOLINT
    auto opt4x = std::optional<Smv>(Smv());          // NOLINT
    auto opt4y = std::optional<Smv>();               // NOLINT
    auto opt5x = std::optional<Scp>(std::in_place);  // NOLINT
    auto opt5y = std::optional<Scp>();               // NOLINT
    auto opt6x = std::optional<Smv2>(std::in_place); // NOLINT
    auto opt6y = std::optional<Smv2>();              // NOLINT
    auto opt7x = std::optional<Scp2>(std::in_place); // NOLINT
    auto opt7y = std::optional<Scp2>();              // NOLINT

    // 次の記述は ill-formed
    // Scp() は prvalue で std::forward されるので Scp(Scp&&) が呼ばれる

    // swap
    using std::swap;
    swap(opt1, opt2);
    EXPECT_EQ(opt1.value(), 12);
    EXPECT_EQ(opt2.value(), 42);

    swap(opt1, opt3);
    EXPECT_FALSE(opt1.has_value());
    EXPECT_EQ(opt3.value(), 12);

    // MoveCtor と MoveAssign が必要
    // swap(opt4x, opt4y);
    // swap(opt5x, opt5y);
    swap(opt6x, opt6y);
    // swap(opt7x, opt7y);

    // reset
    EXPECT_TRUE(opt5x.has_value());
    opt5x.reset();
    EXPECT_FALSE(opt5x.has_value());

    // emplace
    auto opt8x = std::optional<Smv>(); // NOLINT
    auto opt8y = std::optional<Scp>(); // NOLINT
    EXPECT_FALSE(opt8x.has_value());
    EXPECT_FALSE(opt8y.has_value());

    auto& x = opt8x.emplace(); // NOLINT
    auto& y = opt8y.emplace(); // NOLINT
    static_assert(std::is_same_v<decltype(x), Smv&>);
    static_assert(std::is_same_v<decltype(y), Scp&>);
    EXPECT_TRUE(opt8x.has_value());
    EXPECT_TRUE(opt8y.has_value());
}

TEST(
    optional, NonMemberFunctions
)
{
    auto opt1 = std::make_optional(42); // NOLINT
    static_assert(std::is_same_v<decltype(opt1), std::optional<int>>);

    // 引数から直接構築
    auto opt2 = std::make_optional<Sx>(true);
    static_assert(std::is_same_v<decltype(opt2), std::optional<Sx>>);
}

} // namespace
