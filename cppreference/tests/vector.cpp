#include "gtest/gtest.h"
#include <algorithm>
#include <vector>

namespace cppreference
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
    vector, MemberFunctions
)
{
    // 要素数 3 の vector
    // 各要素は Default Construct
    auto vec1 = std::vector<Scp>(3);

    // 要素数 3 で、全ての値を -1 で初期化 (Copy Construct) する vector
    auto vec2 = std::vector<Scp>(3, Scp());
    // auto vec2x = std::vector<Smv>(3, Smv());
    EXPECT_EQ(vec2.size(), 3);

    // vector を copy/move する vector
    auto vec3x = std::vector<Scp>(3);
    auto vec3y = std::vector<Scp>(vec3x);
    auto vec4x = std::vector<Smv>(3);
    auto vec4y = std::vector<Smv>(std::move(vec4x));

    // initializer_list から vector を作成
    auto vec5 = std::vector<int>({1, 2, 3});

    auto vec6 = std::vector<int>{1, 2, 3, 4, 5}; // NOLINT
    vec6.assign(3, 42);                          // NOLINT
    EXPECT_EQ(vec6[0], 42);
    EXPECT_EQ(vec6[1], 42);
    EXPECT_EQ(vec6[2], 42);
    EXPECT_EQ(vec6[3], 4);
    EXPECT_EQ(vec6[4], 5);

    auto vec7 = std::vector<int>{1, 2, 3, 4, 5};  // NOLINT
    auto vec8 = std::vector<int>{6, 7, 8, 9, 10}; // NOLINT
    vec7.assign(vec8.begin(), vec8.end());        // NOLINT
    EXPECT_EQ(vec7, vec8);
}

TEST(
    vector, Capacity
)
{
    std::vector<int> vec1 = {1, 2, 3};
    EXPECT_EQ(3zU, vec1.size());
    EXPECT_EQ(2'305'843'009'213'693'951, vec1.max_size()); // may differ
    vec1.emplace_back(4);                                  // NOLINT
    vec1.emplace_back(5);                                  // NOLINT

    // 足りなくなったら元の容量の 2 倍に増やす
    EXPECT_EQ(6zU, vec1.capacity());
}

TEST(
    vector, Modifiers
)
{
    std::vector<int> vec1 = {1, 2, 3};
    EXPECT_EQ(3zU, vec1.size());
    vec1.clear();
    EXPECT_EQ(0zU, vec1.size());

    auto vec2 = std::vector<int>{1, 2, 3, 4, 5}; // NOLINT
    vec2.emplace_back(6);                        // NOLINT
    EXPECT_EQ(6, vec2.size());
    EXPECT_EQ(10, vec2.capacity());

    vec2.resize(4);
    EXPECT_EQ(4, vec2.size());
    EXPECT_EQ(10, vec2.capacity());

    vec2.resize(7); // NOLINT
    EXPECT_EQ(7, vec2.size());
    EXPECT_EQ(10, vec2.capacity());
}

TEST(
    vector, NonMemberFunctions
)
{
    std::vector<int> vec1 = {1, 2, 3, 4, 5, 1, 6, 7}; // NOLINT
    EXPECT_EQ(8zU, vec1.size());
    const std::size_t n1 = std::erase(vec1, 1);       // NOLINT
    EXPECT_EQ(2zU, n1);
    EXPECT_EQ(6zU, vec1.size());

    std::vector<int> vec2 = {1, 2, 3, 4, 5, 1, 6, 7};      // NOLINT
    EXPECT_EQ(8zU, vec2.size());
    std::erase_if(vec2, [](int i) { return i % 2 == 0; }); // NOLINT
    EXPECT_EQ(5zU, vec2.size());
}

} // namespace cppreference
