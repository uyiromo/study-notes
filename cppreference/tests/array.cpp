#include "gtest/gtest.h"
#include <array>

namespace
{

struct Smv
{
    Smv() = default;
    ~Smv() = default;
    Smv(Smv&&) = default;
    auto operator=(Smv&&) -> Smv& = default;

    Smv(const Smv&) = delete;
    auto operator=(const Smv&) -> Smv& = delete;
};

struct Scp
{
    Scp() = default;
    ~Scp() = default;
    Scp(const Scp&) = default;
    auto operator=(const Scp&) -> Scp& = default;

    Scp(Scp&&) = delete;
    auto operator=(Scp&&) -> Scp& = delete;
};

TEST(
    array, ElementAccess
)
{
    const int x = 42; // NOLINT
    const int y = 43; // NOLINT
    const int z = 44; // NOLINT

    std::array<int, 3>        arr1 = {1, 2, 3};
    std::array<const int, 3>  arr2 = {1, 2, 3};
    std::array<const int*, 3> arr3 = {&x, &y, &z};

    std::array<int, 3>       arr1x = {1, 2, 3};
    const std::array<int, 3> arr1y = {4, 5, 6};

    // at
    static_assert(std::is_same_v<decltype(arr1x.at(0)), int&>);
    static_assert(std::is_same_v<decltype(arr1y.at(0)), const int&>);
    static_assert(std::is_same_v<decltype(arr2.at(0)), const int&>);
    static_assert(std::is_same_v<decltype(arr3.at(0)), const int*&>);
    EXPECT_EQ(arr1x.at(0), 1);
    EXPECT_EQ(arr1y.at(0), 4);

    // operator[]
    static_assert(std::is_same_v<decltype(arr1x[0]), int&>);
    static_assert(std::is_same_v<decltype(arr1y[0]), const int&>);
    EXPECT_EQ(arr1x[0], 1);
    EXPECT_EQ(arr1y[0], 4);

    // front
    static_assert(std::is_same_v<decltype(arr1x.front()), int&>);
    static_assert(std::is_same_v<decltype(arr1y.front()), const int&>);
    EXPECT_EQ(arr1x.front(), 1);
    EXPECT_EQ(arr1y.front(), 4);

    // back
    static_assert(std::is_same_v<decltype(arr1x.back()), int&>);
    static_assert(std::is_same_v<decltype(arr1y.back()), const int&>);
    EXPECT_EQ(arr1x.back(), 3);
    EXPECT_EQ(arr1y.back(), 6);

    // data
    static_assert(std::is_same_v<decltype(arr1x.data()), int*>);
}

TEST(
    array, Iterators
)
{
    std::array<int, 3>             arr1 = {1, 2, 3};
    const std::array<const int, 3> arr2 = {1, 2, 3};

    // begin / cbegin
    static_assert(std::is_same_v<decltype(arr1.begin()), int*>);
    static_assert(std::is_same_v<decltype(arr2.begin()), const int*>);
    static_assert(std::is_same_v<decltype(arr1.cbegin()), const int*>);
    EXPECT_EQ(*arr1.begin(), 1);

    // end / cend
    static_assert(std::is_same_v<decltype(arr1.end()), int*>);
    static_assert(std::is_same_v<decltype(arr2.end()), const int*>);
    static_assert(std::is_same_v<decltype(arr1.cend()), const int*>);
    EXPECT_EQ(*(arr1.end() - 1), 3);

    // rbegin / crbegin
    static_assert(std::is_same_v<decltype(arr1.rbegin()), std::reverse_iterator<int*>>);
    static_assert(std::is_same_v<decltype(arr2.rbegin()), std::reverse_iterator<const int*>>);
    static_assert(std::is_same_v<decltype(arr1.crbegin()), std::reverse_iterator<const int*>>);
    EXPECT_EQ(*arr1.rbegin(), 3);

    // rend / crend
    static_assert(std::is_same_v<decltype(arr1.rend()), std::reverse_iterator<int*>>);
    static_assert(std::is_same_v<decltype(arr2.rend()), std::reverse_iterator<const int*>>);
    static_assert(std::is_same_v<decltype(arr1.crend()), std::reverse_iterator<const int*>>);
    EXPECT_EQ(*(arr1.rend() - 1), 1);
}

TEST(
    array, Capacity
)
{
    std::array<int, 3> arr1 = {1, 2, 3};
    static_assert(std::is_same_v<decltype(arr1.size()), std::size_t>);
}

TEST(
    array, Operations
)
{
    std::array<Scp, 3> arr1x{};
    std::array<Scp, 3> arr1y{};
    std::array<Smv, 3> arr2x{};
    std::array<Smv, 3> arr2y{};

    arr1x.fill(Scp{});
    // arr2.fill(Smv{});

    using std::swap;
    // swap(arr1x, arr1y);
    swap(arr2x, arr2y);
}
TEST(
    array, NonMemberFunctions
)
{
    Scp _a1[3] = {};               // NOLINT
    Smv _a2[3] = {};               // NOLINT

    std::to_array(_a1);            // NOLINT
    std::to_array(std::move(_a2)); // NOLINT
}

} // namespace
