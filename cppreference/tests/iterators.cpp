#include "gtest/gtest.h"
#include <array>
#include <initializer_list>
#include <span>
#include <vector>

namespace
{
TEST(
    container, Span
)
{
    constexpr std::array<int, 6> arr1 = {1, 2, 3, 4, 5, 6}; // NOLINT
    const std::vector<int>       vec1 = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::vector<int>             vec2 = {1, 2, 3, 4, 5, 6}; // NOLINT
    // std::initializer_list<int>   il1 = {1, 2, 3, 4, 5, 6};  // NOLINT

    auto s1 = std::span(arr1);
    static_assert(std::is_same_v<std::span<const int, 6>, decltype(s1)>); // NOLINT
    EXPECT_EQ(s1.size(), 6);
    EXPECT_EQ(s1.extent, 6);

    auto s1x = s1.first(2);
    static_assert(std::is_same_v<std::span<const int, std::dynamic_extent>, decltype(s1x)>);
    EXPECT_EQ(2, s1x.size());
    EXPECT_EQ(std::dynamic_extent, s1x.extent);
    EXPECT_EQ(1, s1x[0]);
    EXPECT_EQ(2, s1x[1]);

    auto s1y = s1.last(2);
    EXPECT_EQ(5, s1y[0]);
    EXPECT_EQ(6, s1y[1]);

    auto s1z = s1.subspan<2, 3>();
    EXPECT_EQ(3, s1z[0]);
    EXPECT_EQ(4, s1z[1]);
    EXPECT_EQ(5, s1z[2]);

    auto s2 = std::span(vec2.begin(), 2);
    static_assert(std::is_same_v<std::span<int, std::dynamic_extent>, decltype(s2)>);
    EXPECT_EQ(s2.size(), 2);
    EXPECT_EQ(s2.extent, std::dynamic_extent);
}

TEST(
    container, MDSpan
)
{
    constexpr std::array<int, 6> arr1 = {1, 2, 3, 4, 5, 6}; // NOLINT
    const std::vector<int>       vec1 = {1, 2, 3, 4, 5, 6}; // NOLINT
    std::vector<int>             vec2 = {1, 2, 3, 4, 5, 6}; // NOLINT
    // std::initializer_list<int>   il1 = {1, 2, 3, 4, 5, 6};  // NOLINT
}
} // namespace
