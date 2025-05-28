#include "gtest/gtest.h"
#include <concepts>
#include <cstdint>
#include <type_traits>

namespace
{

/**
 * @brief ラムダ式の基本構文チェック
 */
TEST(
    lambda, Syntax
)
{
  // tparams 無し
  auto fn1 = [](int __x) { return __x; };
  auto fn2 = [](int __x) noexcept { return __x; };
  auto fn3 = [](int __x) mutable noexcept { return __x; };
  auto fn4 = [](int __x) constexpr noexcept { return __x; };
  auto fn5 = [](int __x) consteval noexcept { return __x; };
  auto fn6 = [](int __x) static noexcept { return __x; };

  // mutable 指定がなければ、コピーキャプチャされた変数は const lvalue
  std::int32_t __v = 1;
  auto fn7 = [__v]() {
    static_assert(!std::is_same_v<decltype((__v)), std::int32_t&>);
    static_assert(std::is_same_v<decltype((__v)), const std::int32_t&>);
  };
  auto fn8 = [__v]() mutable {
    static_assert(std::is_same_v<decltype((__v)), std::int32_t&>);
    static_assert(!std::is_same_v<decltype((__v)), const std::int32_t&>);
  };

  // tparams 有り
  auto fn1_t = []<typename T>(T __x) { return __x; };
  auto fn2_t = []<typename T>(T __x) noexcept { return __x; };
  auto fn3_t = []<typename T>(T __x) mutable noexcept { return __x; };
  auto fn4_t = []<typename T>(T __x) constexpr noexcept { return __x; };
  auto fn5_t = []<typename T>(T __x) consteval noexcept { return __x; };
  auto fn6_t = []<typename T>(T __x) static noexcept { return __x; };

  // concepts も適用可能
  auto fn1_t1 = []<typename T>
    requires std::is_integral_v<T>
  (T __x) { return __x; };

  auto fn1_t2 = []<std::integral T>
    requires std::is_integral_v<T>
  (T __x) { return __x; };
}

/**
 * @brief ClosureType 確認
 */
TEST(
    lambda, ClosureType
)
{
  auto fn1 = [](int __x) { return __x + 1; };
  auto fn2 = []<typename T>(T __x) { return __x + 1; };

  // ret operator()(params) { body }
  // ret の型は推論される
  {
    auto ret11 = fn1.operator()(0);
    auto ret12 = fn1(0);

    EXPECT_EQ(1, ret11);
    EXPECT_EQ(1, ret12);
    static_assert(std::is_same_v<int, decltype(ret11)>);
    static_assert(std::is_same_v<int, decltype(ret12)>);
  }
  {
    auto ret21 = fn2.operator()<std::int32_t>(std::int32_t{1});
    auto ret22 = fn2(std::int32_t{1});

    EXPECT_EQ(2, ret21);
    EXPECT_EQ(2, ret22);
    static_assert(std::is_same_v<std::int32_t, decltype(ret21)>);
    static_assert(std::is_same_v<std::int32_t, decltype(ret22)>);
  }

  //  ClosureType::operator ret(*)(params)()
  // lambda の型は、対応する関数ポインタに変換可能
  int (*fn1_ptr)(int) = fn1;

  // ClosureType::ClosureType()
  // ClosureType::operator=(const ClosureType&)
  // copy/move 可能
  auto fn1_cc(fn1);
  auto fn1_mc(std::move(fn1));
  auto fn1_ca = fn1;
  auto fn1_ma = std::move(fn1);
}

auto Func1(
    std::integral auto... args
) -> std::uint64_t
{
  // template pack を参照キャプチャ
  return [&args...]() { return (args + ...); }();
};

auto Func2(
    std::integral auto... args
) -> std::uint64_t
{
  // template pack をコピーキャプチャ
  return [args...]() { return (args + ...); }();
}

auto Func3(
    std::integral auto... args
) -> std::uint64_t
{
  // template pack を参照キャプチャ
  return [&... vars = args]() { return (vars + ...); }();
};

auto Func4(
    std::integral auto... args
) -> std::uint64_t
{
  // template pack をコピーキャプチャ
  return [... vars = args]() { return (vars + ...); }();
}

struct Scp
{
public:
  Scp() = default;
  Scp(const Scp&) = default;
  Scp(Scp&&) = delete;
  auto operator=(const Scp&) -> Scp& = delete;
  auto operator=(Scp&&) -> Scp& = delete;
  ~Scp() = default;
};

struct Smv
{
public:
  Smv() = default;
  Smv(const Smv&) = delete;
  Smv(Smv&&) = default;
  auto operator=(const Smv&) -> Smv& = delete;
  auto operator=(Smv&&) -> Smv& = delete;
  ~Smv() = default;
};

TEST(
    lambda, Capture
)
{
  thread_local std::uint32_t v_t = 0x1000'0000; // NOLINT
  static std::uint32_t v_s = 0x0100'0000;       // NOLINT
  constexpr std::uint32_t v_c = 0x0010'0000;
  std::uint32_t v_a = 0x0001'0000;              // NOLINT

  Smv smv;
  Scp scp;

  // 自動参照キャプチャ
  auto fn1 = [&]() { return v_t + v_s + v_c + v_a; };
  EXPECT_EQ(fn1(), 0x1111'0000);

  // 自動コピーキャプチャ
  auto fn2 = [=]() { return v_t + v_s + v_c + v_a; };
  EXPECT_EQ(fn2(), 0x1111'0000);

  // コピーキャプチャは copy constructor を呼び出す
  // Copy constructor が delete されている場合は ill-formed
  auto fn3_cp = [scp]() {};
  // auto fn3_mv = [smv]() {};

  // TLS/static 変数はキャプチャ対象にできない
  // auto fn3_t = [&v_t]() { return v_t; };
  // auto fn3_s = [&v_s]() { return v_s; };
  // const 変数はキャプチャ不要
  auto fn3_c = []() { return v_c; };
  auto fn3_a = [&v_a]() { return v_a; };

  // capture は、宣言時の値をキャプチャする
  // コピーキャプチャは変数の値変更に影響されない
  // 参照キャプチャは変数の値変更に影響される
  auto fn4 = [=]() { return v_a; };
  auto fn5 = [&]() { return v_a; };

  v_a = 0x0002'0000; // NOLINT

  EXPECT_EQ(fn4(), 0x0001'0000);
  EXPECT_EQ(fn5(), 0x0002'0000);

  // 各種キャプチャ

  // v_a のみコピーキャプチャ
  auto fn6 = [v_a]() { return v_a; };

  // v_a のみ参照キャプチャ
  auto fn7 = [&v_a]() { return v_a; };

  // template pack キャプチャ
  EXPECT_EQ(std::uint64_t{15}, Func1(1, 2, 3, 4, 5));
  EXPECT_EQ(std::uint64_t{15}, Func2(1, 2, 3, 4, 5));

  struct S
  {
    std::uint32_t v = 0x1111'0000; // NOLINT

    void f()
    {
      // this キャプチャ
      // capture-default でキャプチャされた this は、常に参照キャプチャになる
      auto ff1 = [this]() { return v; };
      auto ff2 = [*this]() { return v; };
      auto ff3 = [&]() { return v; };
      auto ff4 = [=]() { return v; }; // NOLINT

      v = 0x2222'0000;                // NOLINT
      EXPECT_EQ(0x2222'0000, ff1());
      EXPECT_EQ(0x1111'0000, ff2());
      EXPECT_EQ(0x2222'0000, ff3());
      EXPECT_EQ(0x2222'0000, ff4());

      // class member のキャプチャには this か initializer が必要
      // auto ff5 = [v]() { return v; };
      auto ff5 = [this]() { return v; };
      auto ff6 = [__v = v]() { return __v; };
    }
  };
  S __s;
  __s.f();

  // initializer 付きキャプチャ
  auto fn8 = [__x = v_a]() { return __x; };
  auto fn9 = [&__x = v_a]() { return __x; };
  EXPECT_EQ(std::uint64_t{15}, Func3(1, 2, 3, 4, 5));
  EXPECT_EQ(std::uint64_t{15}, Func4(1, 2, 3, 4, 5));

  struct Sbit
  {
    std::uint8_t x : 4 = 0x0F; // NOLINT
    std::uint8_t y = 0x0F;     // NOLINT

    void fn1()                 // NOLINT
    {
      // bit-field はコピーキャプチャのみ (non-const 参照が作成できない)
      auto fb1 = [__x = x]() { return __x; };
      // auto fb2 = [&__x = x]() { return __x; };
    }
  };
}
} // namespace
