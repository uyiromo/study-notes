#include "gtest/gtest.h"
#include <functional>

namespace
{
TEST(
    function, MemberFunctions
)
{
    // default
    auto fn1 = std::function<void(int)>();
    auto fn2 = std::function<void(int)>(nullptr);
    EXPECT_FALSE(fn1);
    EXPECT_FALSE(fn2);
    static_assert(std::is_same_v<typename decltype(fn1)::result_type, void>);

    // copy/move
    auto fn3 = fn1;
    auto fn4 = std::move(fn1);

    // Forward
    auto fn5 = std::function([](int x) { return x * 2; }); // NOLINT
    static_assert(std::is_same_v<typename decltype(fn5)::result_type, int>);
}

struct S
{
    void F(
        int __x
    ) const
    {
        // do something with x
    }
};

TEST(
    function, MemberFunction
)
{
    S s; // NOLINT

    // メンバ関数の第一引数はクラスのポインタ
    auto fn1 = std::function<void(S*, int)>(&S::F);
    fn1(&s, 42); // NOLINT

    // mem_fn
    auto fn2 = std::mem_fn(&S::F);
    fn2(s, 42); // NOLINT
}
} // namespace
