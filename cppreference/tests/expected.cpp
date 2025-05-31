#include "gtest/gtest.h"
#include <exception>
#include <expected>
#include <stdexcept>
#include <version>

namespace
{

struct Sx
{
    Sx(const bool&) {}; // NOLINT
};

struct Sx2
{
    explicit Sx2(bool&&) {}; // NOLINT
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
    expected, MemberFunctions
)
{
    // (1)
    // 値を持たない
    auto exp1 = std::expected<int, std::exception_ptr>{};
    static_assert(std::is_same_v<typename decltype(exp1)::value_type, int>);
    static_assert(std::is_same_v<typename decltype(exp1)::error_type, std::exception_ptr>);

    const auto expScp = std::expected<Scp, std::exception_ptr>();
    auto       expSmv = std::expected<Smv, std::exception_ptr>();
    auto       expBool = std::expected<bool, std::exception_ptr>();

    // (2) (3)
    // copy/move
    // exp3y は Smv を copy しているため ill-formed
    auto exp2 = std::expected(expScp);
    auto exp3x = std::expected(std::move(expSmv));
    // auto exp3y = std::expected(expSmv);

    // (9)
    // 右辺値を渡すと move になる。直接構築する場合は std::in_place を使う。
    // auto exp9x = std::expected<Scp, std::exception_ptr>(Scp());
    auto exp9x = std::expected<Scp, std::exception_ptr>(std::in_place);
    auto exp9y = std::expected<Smv, std::exception_ptr>(Smv());

    // operator=
    const auto expX = std::expected<Scp2, std::exception_ptr>();
    auto       expY = std::expected<Smv2, std::exception_ptr>();

    auto expX2 = std::expected<Scp2, std::exception_ptr>();
    auto expY2 = std::expected<Smv2, std::exception_ptr>();

    expX2 = expX;
    expY2 = std::move(expY);
}

TEST(
    expected, Observers
)
{
    const auto exp1 = std::expected<int, std::exception_ptr>{};
    auto       exp2 = std::expected<int, std::exception_ptr>{};
    auto       exp3 = std::expected<int, std::exception_ptr>(1);

    const auto exp4 = std::expected<int, std::exception>(std::unexpect);
    auto       exp5 = std::expected<int, std::exception>(std::unexpect);

    // operator->
    static_assert(std::is_same_v<decltype(exp1.operator->()), const int*>);
    static_assert(std::is_same_v<decltype(exp2.operator->()), int*>);
    static_assert(std::is_same_v<decltype(std::move(exp2).operator->()), int*>);

    // operator*
    static_assert(std::is_same_v<decltype(*exp1), const int&>);
    static_assert(std::is_same_v<decltype(*exp2), int&>);
    static_assert(std::is_same_v<decltype(*std::move(exp2)), int&&>);

    // operator bool / has_value
    EXPECT_TRUE(exp1.has_value());
    EXPECT_TRUE(bool(exp1));
    EXPECT_TRUE(exp3.has_value());
    EXPECT_TRUE(bool(exp3));
    EXPECT_TRUE(!exp4.has_value());
    EXPECT_TRUE(!bool(exp4));

    // value
    static_assert(std::is_same_v<decltype(exp1.value()), const int&>);
    static_assert(std::is_same_v<decltype(exp2.value()), int&>);
    static_assert(std::is_same_v<decltype(std::move(exp2).value()), int&&>);

    // error
    static_assert(std::is_same_v<decltype(exp4.error()), const std::exception&>);
    static_assert(std::is_same_v<decltype(exp5.error()), std::exception&>);
    static_assert(std::is_same_v<decltype(std::move(exp5).error()), std::exception&&>);

    // value_or
    static_assert(std::is_same_v<decltype(exp1.value_or<bool>(true)), int>);
}

TEST(
    expected, MonadicOperations
)
{
    // TBD
}

} // namespace
