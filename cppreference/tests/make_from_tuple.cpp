#include "gtest/gtest.h"
#include <cstdint>
#include <tuple>

struct Sx
{
    explicit Sx(bool, std::uint32_t) {}; // NOLINT
};

struct Sy
{
    explicit Sy(bool&&, std::uint32_t&&) {}; // NOLINT
};

TEST(
    make_from_tuple, basic
)
{
    constexpr bool          b = true;        // NOLINT
    constexpr std::uint32_t v = 0x1111'0000; // NOLINT

    auto tpl1 = std::make_tuple(b, v);
    static_assert(std::is_same_v<decltype(tpl1), std::tuple<bool, std::uint32_t>>);

    auto tpl2 = std::tie(b, v);
    static_assert(std::is_same_v<decltype(tpl2), std::tuple<const bool&, const std::uint32_t&>>);

    auto tpl3 = std::forward_as_tuple(true, std::uint32_t{1});
    static_assert(std::is_same_v<decltype(tpl3), std::tuple<bool&&, std::uint32_t&&>>);

    std::make_from_tuple<Sx>(tpl1);
    std::make_from_tuple<Sx>(tpl2);
    std::make_from_tuple<Sx>(tpl3);

    // 内部的には各要素を std::get しているので、tuple の要素の型は tuple の cv
    // LR に依存する
    // std::make_from_tuple<Sy>(tpl1);
    // std::make_from_tuple<Sy>(tpl2);
    // std::make_from_tuple<Sy>(tpl3);
    std::make_from_tuple<Sy>(std::move(tpl3));
}
