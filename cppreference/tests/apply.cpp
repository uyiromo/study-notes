#include "gtest/gtest.h"
#include <tuple>

namespace
{
template <typename T>
auto fn_t(
    T first, T second
) -> T
{
    return first + second;
}

auto fn(
    int a, int b // NOLINT
) -> int
{
    return a + b;
}

struct S
{
    auto operator()(
        int a, int b // NOLINT
    ) const -> int
    {
        return a + b;
    }
};

TEST(
    apply, basic
)
{
    EXPECT_EQ(5, std::apply(fn, std::make_tuple(2, 3))); // NOLINT

    // template の呼び出しではないので type deduction は発生しない
    // std::apply(add_generic, std::make_pair(2.0F, 3.0F)); // NOLINT
    EXPECT_DOUBLE_EQ(5.0, std::apply(fn_t<float>, std::make_tuple(2.0F, 3.0F))); // NOLINT

    // lambda は型推論が無くても object になるので可能
    auto lmb = [](auto a, auto b) {                       // NOLINT
        return a + b;
    };
    EXPECT_EQ(5, std::apply(lmb, std::make_tuple(2, 3))); // NOLINT

    // 対応する operator() があればそれも可能
    EXPECT_EQ(5, std::apply(S(), std::make_tuple(2, 3))); // NOLINT
}

} // namespace
