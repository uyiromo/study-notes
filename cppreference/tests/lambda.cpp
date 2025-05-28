#include "gtest/gtest.h"
#include <concepts>
#include <cstdint>
#include <type_traits>

TEST(
    lambda, Basic
)
{
  // tparams 無し
  auto f1 = [](int x) { return x + 1; };
  auto f2 = [](int x) noexcept { return x + 1; };
  auto f3 = [](int x) mutable noexcept { return x + 1; };
  auto f4 = [](int x) constexpr noexcept { return x + 1; };
  auto f5 = [](int x) consteval noexcept { return x + 1; };
  auto f6 = [](int x) static noexcept { return x + 1; };

  // tparams 有り
  auto t1 = []<typename T>(T x) { return x + 1; };
  auto t0 = []<typename T>
    requires std::is_integral_v<T>
  (T x) { return x + 1; };
  auto t2 = []<typename T>(T x) noexcept { return x + 1; };
  auto t3 = []<typename T>(T x) mutable noexcept { return x + 1; };
  auto t4 = []<typename T>(T x) constexpr noexcept { return x + 1; };
  auto t5 = []<typename T>(T x) consteval noexcept { return x + 1; };
  auto t6 = []<typename T>(T x) static noexcept { return x + 1; };
}

TEST(
    lambda, ClosureType
)
{
  auto f1 = [](int x) { return x + 1; };
  auto t1 = []<typename T>(T x) { return x + 1; };

  // ret operator()(params) { body }
  // ret の型は推論される
  {
    auto ret = f1.operator()(0);
    EXPECT_EQ(ret, 1);
    static_assert(std::is_same_v<int, decltype(ret)>);
  }
  {
    auto ret = f1(0);
    EXPECT_EQ(ret, 1);
    static_assert(std::is_same_v<int, decltype(f1(0))>);
  }
  {
    auto ret = t1.operator()<std::int32_t>(std::int32_t{1});
    EXPECT_EQ(ret, 2);
    static_assert(std::is_same_v<std::int32_t, decltype(ret)>);
  }
  {
    auto ret = t1(std::int32_t{1});
    EXPECT_EQ(ret, 2);
    static_assert(std::is_same_v<std::int32_t, decltype(ret)>);
  }

  //  ClosureType::operator ret(*)(params)()
  // lambda の型は、対応する関数ポインタに変換可能
  int (*f1_ptr)(int) = f1;

  // ClosureType::ClosureType()
  // ClosureType::operator=(const ClosureType&)
  // copy/move 可能
  auto f1_cpctor(f1);
  auto f1_mvctor(std::move(f1));
  auto f1_cpa = f1;
  auto f1_mva = std::move(f1);
}

template <std::integral... Ts>
std::uint64_t Func1(
    Ts... ts
)
{
  auto f = [&ts...]() { return (ts + ...); };
  return f();
};

template <std::integral... Ts>
std::uint64_t Func2(
    Ts... ts
)
{
  auto f = [ts...]() { return (ts + ...); };
  return f();
};

class C1
{
public:
  C1() = default;
  C1(const C1&) = default;
  C1(C1&&) = delete;
  auto operator=(const C1&) -> C1& = delete;
  auto operator=(C1&&) -> C1& = delete;
};

class C2
{
public:
  C2() = default;
  C2(const C2&) = delete;
  C2(C2&&) = default;
  C2& operator=(const C2&) = delete;
  C2& operator=(C2&&) = delete;
};

TEST(
    lambda, LambdaCapture
)
{
  thread_local std::uint32_t v_t = 0x1000'0000;
  static std::uint32_t v_s = 0x0100'0000;
  constexpr std::uint32_t v_c = 0x0010'0000;
  std::uint32_t v_a = 0x0001'0000;

  C1 c1;
  C2 c2;

  // 参照キャプチャ (lambda の中で参照される変数を自動キャプチャ)
  auto f1 = [&]() {
    std::uint32_t tmp = 0;
    tmp += v_t;
    tmp += v_s;
    tmp += v_c;
    tmp += v_a;
    return tmp;
  };
  EXPECT_EQ(f1(), 0x1111'0000);

  // コピーキャプチャ
  auto f2 = [=]() {
    std::uint32_t tmp = 0;
    tmp += v_t;
    tmp += v_s;
    tmp += v_c;
    tmp += v_a;
    return tmp;
  };
  EXPECT_EQ(f2(), 0x1111'0000);

  // コピーキャプチャは copy constructor を呼び出す
  // C2 はコピーキャプチャ不可
  auto f2_c1 = [c1]() {};
  // auto f2_c2 = [c2]() {};

  // capture は、宣言時の値をキャプチャする
  // コピーキャプチャは変数の値変更に影響されない
  // 参照キャプチャは変数の値変更に影響される
  auto f3 = [=]() { return v_a; };
  auto f4 = [&]() { return v_a; };

  v_a = 0x0002'0000;

  EXPECT_EQ(f3(), 0x0001'0000);
  EXPECT_NE(f3(), 0x0002'0000);

  EXPECT_EQ(f4(), 0x0002'0000);
  EXPECT_NE(f4(), 0x0001'0000);

  // 各種キャプチャ

  // v_a のみコピーキャプチャ
  auto f5 = [v_a]() { return v_a; };

  // v_a のみ参照キャプチャ
  auto f6 = [&v_a]() { return v_a; };

  // template pack キャプチャ
  EXPECT_EQ(std::uint64_t{15}, Func1(1, 2, 3, 4, 5));
  EXPECT_EQ(std::uint64_t{15}, Func2(1, 2, 3, 4, 5));

  struct S
  {
    std::uint32_t v = 0x1111'0000;

    void f()
    {
      // this キャプチャ
      // capture-default でキャプチャされた this は、常に参照キャプチャになる
      auto ff1 = [this]() { return v; };
      auto ff2 = [*this]() { return v; };
      auto ff3 = [&]() { return v; };
      auto ff4 = [=]() { return v; };

      v = 0x2222'0000;
      EXPECT_EQ(0x2222'0000, ff1());
      EXPECT_EQ(0x1111'0000, ff2());
      EXPECT_EQ(0x2222'0000, ff3());
      EXPECT_EQ(0x2222'0000, ff4());
    }
  };
  S().f();

  // initializer 付きキャプチャ
  auto f7 = [x = v_a]() { return x; };
}
