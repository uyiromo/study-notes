#include "gtest/gtest.h"
#include <bits/types/struct_sched_param.h>
#include <initializer_list>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace
{
struct Scp;
} // namespace

template <>
struct std::hash<::Scp>
{
    auto operator()(const Scp&) const -> std::size_t // NOLINT
    {
        return 0; // NOLINT
    }
};

namespace
{
struct Scp // NOLINT
{
    Scp() = default;
    ~Scp() = default;
    Scp(const Scp&) = delete;
    auto operator=(const Scp&) -> Scp& = delete;
    auto operator==(const Scp&) const -> bool // NOLINT
    {
        return true; // NOLINT
    }

    Scp(Scp&&) = delete;
    auto operator=(Scp&&) -> Scp& = delete;
};

TEST(
    UAC, Basics
)
{
    const auto vec1 = std::vector<int>({1, 2, 3, 4, 5});                                                // NOLINT
    const auto vec2 = std::vector<std::pair<std::string, int>>({{"one", 1}, {"two", 2}, {"three", 3}}); // NOLINT

    // unordered_set
    // iterator の中身は const Key&
    auto us1 = std::unordered_set<int>({1, 2, 3, 4, 5});          // NOLINT
    auto us2 = std::unordered_set<int>(vec1.begin(), vec1.end()); // NOLINT
    static_assert(std::is_same_v<decltype(us1.begin()), std::unordered_set<int>::iterator>);
    static_assert(std::is_same_v<decltype(*us1.begin()), const int&>);

    // unordered_map
    // iterator の中身は std::pair<const Key, T>&
    auto um1 = std::unordered_map<std::string, int>({{"one", 1}, {"two", 2}, {"three", 3}}); // NOLINT
    auto um2 = std::unordered_map<std::string, int>(vec2.begin(), vec2.end());               // NOLINT
    static_assert(std::is_same_v<decltype(um1.begin()), std::unordered_map<std::string, int>::iterator>);
    static_assert(std::is_same_v<decltype(*um1.begin()), std::pair<const std::string, int>&>);

    // unordered_set / uunordered_multiset
    auto us0 = std::unordered_set<int>({1, 2, 3, 4, 5, 1});       // NOLINT
    auto ums0 = std::unordered_multiset<int>({1, 2, 3, 4, 5, 1}); // NOLINT
    EXPECT_EQ(5, us0.size());
    EXPECT_EQ(6, ums0.size());

    // unordered_map / unordered_multimap
    auto um0 = std::unordered_map<std::string, int>({{"one", 1}, {"two", 2}, {"three", 3}, {"one", 4}});       // NOLINT
    auto umm0 = std::unordered_multimap<std::string, int>({{"one", 1}, {"two", 2}, {"three", 3}, {"one", 4}}); // NOLINT
    EXPECT_EQ(3, um0.size());
    EXPECT_EQ(4, umm0.size());
}

template <typename T>
void EqUS(
    const std::unordered_set<T>&    us, // NOLINT
    const std::initializer_list<T>& values
)
{
    for (const auto& v : values) // NOLINT
    {
        EXPECT_NE(us.find(v), us.end());
        EXPECT_TRUE(us.contains(v));
    }
}

TEST(
    UAC, Modifiers
)
{
    // insert
    auto vec1 = std::vector<int>({6, 7});                // NOLINT
    auto us1 = std::unordered_set<int>({1, 2, 3, 4, 5}); // NOLINT
    us1.insert(0);
    EqUS(us1, {0, 1, 2, 3, 4, 5});                       // NOLINT
    us1.insert({-1, -2});
    EqUS(us1, {-2, -1, 0, 1, 2, 3, 4, 5});               // NOLINT
    us1.insert(vec1.begin(), vec1.end());
    EqUS(us1, {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7});         // NOLINT

    // emplace
    auto us2 = std::unordered_set<int>({1, 2, 3, 4, 5}); // NOLINT
    us2.emplace(0);
    EqUS(us2, {0, 1, 2, 3, 4, 5});                       // NOLINT

    // erase
    auto us3 = std::unordered_set<int>({1, 2, 3, 4, 5}); // NOLINT
    us3.erase(3);
    EqUS(us3, {1, 2, 4, 5});                             // NOLINT
    us3.erase(us3.find(2));
    EqUS(us3, {1, 4, 5});                                // NOLINT

    // extract & insert
    auto us4 = std::unordered_set<int>({1, 2, 3, 4, 5}); // NOLINT
    auto us4x = std::unordered_set<int>({6, 7});         // NOLINT
    auto node = us4.extract(3);
    static_assert(std::is_same_v<decltype(node), std::unordered_set<int>::node_type>);
    EqUS(us4, {1, 2, 4, 5});                             // NOLINT
    us4.insert(std::move(node));
    EqUS(us4, {1, 2, 3, 4, 5});                          // NOLINT

    auto usX = std::unordered_set<Scp>();                // NOLINT
    auto nodeX = usX.extract(Scp());                     // NOLINT

    // merge
    auto us5 = std::unordered_set<int>({1, 2, 3, 4, 5}); // NOLINT
    auto us5x = std::unordered_set<int>({6, 7});         // NOLINT
    us5.merge(us5x);
    EqUS(us5, {1, 2, 3, 4, 5, 6, 7});                    // NOLINT
}

} // namespace
