#include "gtest/gtest.h"
#include <forward_list>

namespace
{

TEST(
    forward_list, Operations
)
{
    auto fl0 = std::forward_list<int>({3, 4, 5, 1, -1});   // NOLINT
    auto fl1 = fl0;

    auto fl0x = std::forward_list<int>({6, 8, 10, 2, -2}); // NOLINT
    auto fl1x = fl0x;

    // sort
    fl1.sort();
    EXPECT_EQ(fl1, (std::forward_list<int>({-1, 1, 3, 4, 5})));

    fl1.sort(std::greater<>());
    EXPECT_EQ(fl1, (std::forward_list<int>({5, 4, 3, 1, -1})));

    // merge
    fl1.sort();
    fl1x.sort();
    fl1.merge(fl1x);
    EXPECT_EQ(fl1, (std::forward_list<int>({-2, -1, 1, 2, 3, 4, 5, 6, 8, 10})));

    fl1 = fl0;
    fl1x = fl0x;
    fl1.sort(std::greater<>());
    fl1x.sort(std::greater<>());
    fl1.merge(fl1x, std::greater<>());
    EXPECT_EQ(fl1, (std::forward_list<int>({10, 8, 6, 5, 4, 3, 2, 1, -1, -2})));
}
} // namespace
