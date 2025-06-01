#include "gtest/gtest.h"
#include <functional>

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

TEST(
    function, bind
)
{
    auto f = [](int n1, int n2, int n3, const int& n4, int n5) // NOLINT
    { return std::to_string(n1) + std::to_string(n2) + std::to_string(n3) + std::to_string(n4) + std::to_string(n5); };

    // 12,34,56,78,90
    // n2 = 34,
    // n1 = 12
    constexpr int x = 78;                                                                     // NOLINT
    auto          b1 = std::bind(f, std::placeholders::_2, 34, std::placeholders::_1, x, 90); // NOLINT

    // n1 = _2 (2nd arg), n3 = _1 (1st arg) に対応する
    EXPECT_EQ(b1(56, 12), "1234567890"); // NOLINT
}

} // namespace
