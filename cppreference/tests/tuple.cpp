#include "gtest/gtest.h"
#include <cstdint>
#include <tuple>
#include <type_traits>
#include <utility>

namespace
{
struct S
{
    S() = delete;
};

struct Scp
{
    Scp(Scp&&) = delete;
    auto operator=(Scp&&) -> Scp& = delete;
    auto operator=(const Scp&) -> Scp& = delete;

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

struct Sint
{
    Sint() = delete;
    Sint(const Sint&) = delete;
    Sint(Sint&&) = delete;
    auto operator=(const Sint&) -> Sint& = delete;
    auto operator=(Sint&&) -> Sint& = delete;

    Sint(int __x) {};
    ~Sint() = default;
};

TEST(
    tuple, Constructor
)
{
    using T = bool;
    using U = std::uint32_t;

    constexpr T   b = true;        // NOLINT
    constexpr U   v = 0x1111'0000; // NOLINT
    constexpr Scp scp;             // NOLINT
    constexpr Smv smv;             // NOLINT

    /*
      (1)
      要素を default Ctor する
   */
    // std::tuple<int, S> tpl1x; // ill-formed
    std::tuple<T, U> tpl1;
    static_assert(std::is_same_v<decltype(std::get<0>(tpl1)), T&>);
    static_assert(std::is_same_v<decltype(std::get<1>(tpl1)), U&>);

    /*
      (2)
      要素を direct construct (Copy Ctor) する
    */
    // std::tuple<T, Scp> tpl2m(b, Smv()); // ill-formed
    std::tuple<T, U>   tpl2(b, v);
    std::tuple<T, Scp> tpl2c(b, Scp());

    /*
     (3)
     要素を convert construct (std::forward<UTypes>(args)) する
    */
    std::tuple<T, U>    tpl3(b, v);
    std::tuple<T, Scp>  tpl3c(b, Scp());
    std::tuple<T, Smv>  tpl3m(b, Smv());
    std::tuple<T, Sint> tpl3i(b, 1); // Sint(int) が呼ばれる

    // (4) (5) (6) (7)
    // convert construct 可能なら copy/move 可能
    std::tuple<T, U>       tpl4x(b, v);
    const std::tuple<T, U> tpl4y(b, v);

    std::tuple<T, Sint> tpl4(tpl4x);
    std::tuple<T, Sint> tpl5(tpl4y);
    std::tuple<T, Sint> tpl6(std::move(tpl4x));
    std::tuple<T, Sint> tpl7(std::move(tpl4y)); // NOLINT

    // (8) (9) (10) (11)
    // 全く同じ型の pair から構築可能
    std::pair<T, U>  pa1(b, v);
    std::tuple<T, U> tpl8(pa1);

    // (12)
    // tuple-like な型で要素を変換可能なら構築可能
    std::pair<T, Sint> tpl9(pa1);
}

TEST(
    tuple, Swap
)
{
    using T = bool;
    using U = std::uint32_t;

    std::tuple<T, U> tpl1(false, 0x1111'0000); // NOLINT
    std::tuple<T, U> tpl2(true, 0x0000'1111);  // NOLINT

    // 要素同士を swap する
    std::swap(tpl1, tpl2);
    EXPECT_EQ(std::get<0>(tpl1), true);
    EXPECT_EQ(std::get<1>(tpl1), 0x0000'1111);
    EXPECT_EQ(std::get<0>(tpl2), false);
    EXPECT_EQ(std::get<1>(tpl2), 0x1111'0000);

    // ADL
    using std::swap;
    swap(tpl1, tpl2);
    EXPECT_EQ(std::get<0>(tpl1), false);
    EXPECT_EQ(std::get<1>(tpl1), 0x1111'0000);
    EXPECT_EQ(std::get<0>(tpl2), true);
    EXPECT_EQ(std::get<1>(tpl2), 0x0000'1111);

    // Sint と int が swap 不可能なので ill-formed
    // tpl4 の右辺を Sint(0) にはできない
    // => CopyCtor もしくは MoveCtor がない
    std::tuple<T, int>  tpl3(true, 0x0000'1111); // NOLINT
    std::tuple<T, Sint> tpl4(false, 0);          // NOLINT

    // std::swap(std::tuple) は全ての型が同じでないと不可
    /* template< class... Types >
       constexpr void swap(
           const std::tuple<Types...>& lhs,
           const std::tuple<Types...>& rhs
       ) noexcept(...);
    */
    // swap(tpl3, tpl4);                            // ill-formed
}

TEST(
    tuple, make_tuple
)
{
    /*
        template< class... Types >
        std::tuple<VTypes...> make_tuple( Types&&... args );
    */
    // VTypes は std::decay<Ti>::type
    // => arr/function 以外は CV が剥がれる
    // reference も剥がれる
    // decay の結果が参照なら参照

    auto tpl1 = std::make_tuple(true, std::uint32_t{0x1111'0000}); // NOLINT
    static_assert(std::is_same_v<decltype(tpl1), std::tuple<bool, std::uint32_t>>);

    constexpr bool          b = true;                              // NOLINT
    constexpr std::uint32_t i = 0x1111'0000;                       // NOLINT

    // const が外れる
    auto tpl2 = std::make_tuple(b, i);
    static_assert(std::is_same_v<decltype(tpl2), std::tuple<bool, std::uint32_t>>);

    constexpr std::array<int, 2> a = {1, 2}; // NOLINT

    // std::array は decay 対象外
    auto tpl3 = std::make_tuple(a, b);
    static_assert(std::is_same_v<decltype(tpl3), std::tuple<std::array<int, 2>, bool>>);

    constexpr int a2[3] = {1, 2, 3}; // NOLINT

    // decay 対象
    // 配列はポインタに変換される (CV は保持される)
    auto tpl4 = std::make_tuple(a2, b);
    static_assert(std::is_same_v<decltype(tpl4), std::tuple<const int*, bool>>);

    const Scp scp;

    // CopyCtor されるので Smv は不可
    auto tpl5 = std::make_tuple(scp, b);

    auto tpl6 = std::make_tuple(std::move(true), std::move(1)); // NOLINT
    static_assert(std::is_same_v<decltype(tpl6), std::tuple<bool, int>>);
}

TEST(
    tuple, tie
)
{
    constexpr bool          b = true;        // NOLINT
    constexpr std::uint32_t v = 0x1111'0000; // NOLINT

    auto tpl1 = std::tie(b, v);
    static_assert(std::is_same_v<decltype(tpl1), std::tuple<const bool&, const std::uint32_t&>>);
}

TEST(
    tuple, forward_as_tuple
)
{
    constexpr bool          b = true;        // NOLINT
    constexpr std::uint32_t v = 0x1111'0000; // NOLINT

    // lvalue reference
    auto tpl1 = std::forward_as_tuple(b, v);
    static_assert(std::is_same_v<decltype(tpl1), std::tuple<const bool&, const std::uint32_t&>>);

    // rvalue reference
    auto tpl2 = std::forward_as_tuple(true, std::uint32_t{1});
    static_assert(std::is_same_v<decltype(tpl2), std::tuple<bool&&, std::uint32_t&&>>);
}

TEST(
    tuple, tuple_cat
)
{
    constexpr bool          b = true;        // NOLINT
    constexpr std::uint32_t v = 0x1111'0000; // NOLINT

    // lvalue reference
    auto tpl1 = std::forward_as_tuple(b, v);
    static_assert(std::is_same_v<decltype(tpl1), std::tuple<const bool&, const std::uint32_t&>>);

    // rvalue reference
    auto tpl2 = std::forward_as_tuple(true, std::uint32_t{1});
    static_assert(std::is_same_v<decltype(tpl2), std::tuple<bool&&, std::uint32_t&&>>);

    // direct-construct するため、CopyCtor が必要
    // auto tpl3 = std::tuple_cat(tpl1, tpl2); // ill-formed
}

TEST(
    lambda, get
)
{
    constexpr bool          b = true;        // NOLINT
    constexpr std::uint32_t v = 0x1111'0000; // NOLINT

    auto tpl1 = std::make_tuple(b, v);
    static_assert(std::is_same_v<decltype(tpl1), std::tuple<bool, std::uint32_t>>);

    const auto tpl2 = std::make_tuple(b, v);
    static_assert(std::is_same_v<decltype(tpl2), const std::tuple<bool, std::uint32_t>>);

    auto tpl3 = std::forward_as_tuple(true, std::uint32_t{1});
    static_assert(std::is_same_v<decltype(tpl3), std::tuple<bool&&, std::uint32_t&&>>);

    // non-const lvalue
    static_assert(std::is_same_v<decltype(std::get<0>(tpl1)), bool&>);

    // const lvalue
    static_assert(std::is_same_v<decltype(std::get<0>(tpl2)), const bool&>);

    // non-const rvalue
    static_assert(std::is_same_v<decltype(std::get<1>(std::move(tpl1))), std::uint32_t&&>);

    // const rvalue
    static_assert(std::is_same_v<
                  decltype(std::get<1>(std::move(tpl2))), // NOLINT
                  const std::uint32_t&&>);

    // reference collapsing によって、T&& の & は T&
    static_assert(std::is_same_v<decltype(std::get<0>(tpl3)), bool&>);
}

TEST(
    tuple, helper_classes
)
{
    constexpr bool          b = true;        // NOLINT
    constexpr std::uint32_t v = 0x1111'0000; // NOLINT

    // bool, std::uint32_t
    auto tpl1 = std::make_tuple(b, v);

    // const bool&, const std::uint32_t&
    const auto tpl2 = std::tie(b, v);

    // bool&&, std::uint32_t&&
    auto tpl3 = std::forward_as_tuple(true, std::uint32_t{1});

    // tuple_size
    static_assert(std::is_same_v<std::size_t, std::tuple_size<decltype(tpl1)>::value_type>);
    EXPECT_EQ(2, std::tuple_size_v<decltype(tpl1)>);

    // tuple_element
    static_assert(std::is_same_v<bool, std::tuple_element_t<0, decltype(tpl1)>>);
    static_assert(std::is_same_v<std::uint32_t, std::tuple_element_t<1, decltype(tpl1)>>);

    static_assert(std::is_same_v<const bool&, std::tuple_element_t<0, decltype(tpl2)>>);
    static_assert(std::is_same_v<const std::uint32_t&, std::tuple_element_t<1, decltype(tpl2)>>);

    static_assert(std::is_same_v<bool&&, std::tuple_element_t<0, decltype(tpl3)>>);
    static_assert(std::is_same_v<std::uint32_t&&, std::tuple_element_t<1, decltype(tpl3)>>);
}
} // namespace
