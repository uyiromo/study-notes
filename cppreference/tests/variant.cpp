#include "gtest/gtest.h"
#include <cstddef>
#include <string>
#include <type_traits>
#include <variant>

namespace
{
struct Scp
{
    Scp(Scp&&) = delete;
    auto operator=(const Scp&) -> Scp& = delete;
    auto operator=(Scp&&) -> Scp& = delete;

    Scp() = default;
    Scp(const Scp&) = default;
    ~Scp() = default;
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
    variant, MemberFunctions
)
{
    // デフォルトコンストラクタ
    auto var1 = std::variant<Scp, Smv>();
    static_assert(std::is_same_v<decltype(var1), std::variant<Scp, Smv>>);

    // std::in_place_t を使ったコンストラクタ
    auto var1x = std::variant<int, const int>(std::in_place_type<int>);
    auto var1y = std::variant<int, const int>(std::in_place_type<const int>);
    // 要素を特定できないため ill-formed
    // auto var1z = std::variant<int, int>(std::in_place_type<int>);

    // 要素位置を指定して直接構築
    auto var2 = std::variant<Scp2, Smv2>(std::in_place_index<0>);
    auto var2x = std::variant<Scp2, Smv2>(std::in_place_index<0>);
    auto var2y = std::variant<Scp2, Smv2>(std::in_place_index<1>);

    // 両方 ill-formed (Smv2 が CopyAssign 不可能)
    // var2 = var2x;
    // var2 = var2y;
}

TEST(
    variant, Observers
)
{
    auto var1 = std::variant<Scp, Smv>();
    auto var2 = std::variant<Scp, Smv>(std::in_place_type<Smv>);
    auto var3 = std::variant<Scp, Smv>(std::in_place_index<1>);

    static_assert(std::is_same_v<decltype(var1.index()), size_t>);
    EXPECT_EQ(var1.index(), std::size_t(0));
    EXPECT_EQ(var2.index(), std::size_t(1));
    EXPECT_EQ(var3.index(), std::size_t(1));
}

TEST(
    variant, Modifiers
)
{
    auto var1 = std::variant<Scp, Smv>();
    auto var2 = std::variant<Scp, Smv>(std::in_place_type<Smv>);

    // emplace
    // 型指定
    auto& x = var1.emplace<Smv>(); // NOLINT
    static_assert(std::is_same_v<decltype(x), Smv&>);

    // 位置指定
    auto& y = var1.emplace<1>(); // NOLINT
    static_assert(std::is_same_v<decltype(y), Smv&>);
}

// ラムダ式オーバーロード
// 1. ラムダ式を全て継承する
// 2. `using` で、operator() を全て継承する
//     => overloaded.operator() でオーバーロードされる
template <class... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};

TEST(
    variant, NonMemberFunctions
)
{
    auto var1 = std::variant<std::int32_t, double, std::string>();
    auto var2 = std::variant<std::int32_t, double, bool>();

    // fn1 は doutble と std::string に対するオーバーロードが無いため不可
    auto fn1 = [](std::int32_t __x) { return 2 * __x; };
    // std::visit(fn1, var1);

    // fn2 は (2*std::string) という式が ill-formed になるため不可
    auto fn2 = [](auto&& arg) { return 2 * arg; };
    // std::visit(fn2, var1);

    // 返り値の型は、全ての結果に対応する型
    auto fn3 = [](auto&& arg) -> decltype(var1) { return arg + arg; };
    std::visit(fn3, var1);

    // これは全て std::string になるため可能
    auto fn3x = [](auto&& arg) -> std::string { return std::to_string(arg) + std::to_string(arg); };
    std::visit(fn3x, var2);

    // 複数の variant を引数に取れる
    auto fn4 = [](auto&& arg1, auto&& arg2) -> std::string {
        if constexpr (std::is_same_v<std::remove_cvref_t<decltype(arg1)>, std::string>)
            {
                return arg1 + std::to_string(arg2);
            }
        else
            {
                return std::to_string(arg1) + std::to_string(arg2);
            }
    };
    std::visit(fn4, var1, var2);

    // ラムダ式オーバーロード
    std::visit(
        overloaded{
            [](const std::int32_t arg) { std::cout << arg << ' '; },
            [](const double arg) { std::cout << std::fixed << arg << ' '; },
            [](const std::string& arg) { std::cout << arg << ' '; }
        },
        var1
    );

    // 最初の型
    auto var3 = std::variant<std::int32_t, double, std::string>();
    EXPECT_TRUE(std::holds_alternative<std::int32_t>(var3));
    EXPECT_FALSE(std::holds_alternative<std::string>(var3));

    var3 = std::string("Hello, World!");
    EXPECT_FALSE(std::holds_alternative<std::int32_t>(var3));
    EXPECT_TRUE(std::holds_alternative<std::string>(var3));

    // const があれば違う型
    auto var4 = std::variant<std::int32_t, const std::int32_t>();
    EXPECT_TRUE(std::holds_alternative<std::int32_t>(var4));

    // 同じ型が 2 回あるので ill-formed
    auto var4x = std::variant<std::int32_t, std::int32_t>();
    // EXPECT_TRUE(std::holds_alternative<std::int32_t>(var4x));

    /*
        std::get
    */
    auto var5 = std::variant<std::int32_t, double, std::string>();
    static_assert(std::is_same_v<decltype(std::get<std::int32_t>(var5)), std::int32_t&>);
    static_assert(std::is_same_v<decltype(std::get<std::int32_t>(std::as_const(var5))), const std::int32_t&>);
    static_assert(std::is_same_v<decltype(std::get<std::int32_t>(std::move(var5))), std::int32_t&&>);

    static_assert(std::is_same_v<decltype(std::get<0>(var5)), std::int32_t&>);
    static_assert(std::is_same_v<decltype(std::get<0>(std::as_const(var5))), const std::int32_t&>);
    static_assert(std::is_same_v<decltype(std::get<0>(std::move(var5))), std::int32_t&&>);

    /*
        std::get_if
    */
    auto       var5x = std::variant<const std::int32_t, double, std::string>();
    const auto var5y = std::variant<std::int32_t, double, std::string>();

    static_assert(std::is_same_v<decltype(std::get_if<std::int32_t>(&var5)), std::int32_t*>);
    static_assert(std::is_same_v<decltype(std::get_if<const std::int32_t>(&var5)), const std::int32_t*>);
    static_assert(std::is_same_v<decltype(std::get_if<std::int32_t>(&var5x)), std::int32_t*>);
    static_assert(std::is_same_v<decltype(std::get_if<const std::int32_t>(&var5x)), const std::int32_t*>);

    static_assert(std::is_same_v<decltype(std::get_if<0>(&var5)), std::int32_t*>);
    static_assert(std::is_same_v<decltype(std::get_if<0>(&var5x)), const std::int32_t*>);
}

TEST(
    variant, HelperClasses
)
{
    struct S
    {
        S(int __x) {};
    };

    // S() ができないので ill-formed
    // std::variant<S> var1;
    std::variant<std::monostate, S> var2;

    static_assert(std::is_same_v<typename std::variant_size<decltype(var2)>::value_type, std::size_t>);
    static_assert(std::variant_size_v<decltype(var2)> == 2);
}

} // namespace
