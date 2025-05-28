#include "gtest/gtest.h"
#include <type_traits>
#include <utility>

template <typename T, typename U> void test_pair_member_types(T &&t, U &&u) {
  auto p = std::pair<T, U>(t, u);
  static_assert(std::is_same_v<decltype(p.first), T>);
  static_assert(std::is_same_v<decltype(p.second), U>);
}

TEST(pair, MemberTypes) {
  int i = 0;

  test_pair_member_types<int, double>(0, 0.0);
  test_pair_member_types<int &, double>(i, 0.0);
}
