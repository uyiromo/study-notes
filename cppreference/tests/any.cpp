#include "gtest/gtest.h"
#include <any>

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

struct Sx
{
    explicit Sx(bool&&) {}; // NOLINT
};

struct Sx2
{
    explicit Sx2(const bool&) {}; // NOLINT
};

struct Sx3
{
    explicit Sx3(bool&) {}; // NOLINT
};

struct Sx4
{
    explicit Sx4(bool) {};  // NOLINT
};

struct Sy                   // NOLINT
{
    explicit Sy(bool&&) {}; // NOLINT
    Sy(const Sy&) = default;

    Sy(Sy&&) = delete;
};

TEST(
    any, MemberFunctions
)
{
    const auto s1 = Scp(); // NOLINT

    // Smv は CopyCtor が無いので any の要件を満たさない
    // Scp は MoveCtor が無いので右辺値は与えられない
    std::any any1;
    // std::any any2{Smv()};
    // std::any any3{Scp()};
    std::any any3{s1};

    // 型を指定して直接構築
    // Sy は MoveCtor が無いので ill-formed
    std::any any4{Sx(true)};
    // std::any any5{Sy(true)};

    // MoveCtor が無い場合、in_place
    std::any any6(std::in_place_type<Sy>, true);
};

TEST(
    any, Modifiers
)
{
    std::any any1;
    any1.emplace<bool>(true);
    any1.emplace<std::string>();
}

TEST(
    any, Observers
)
{
    std::any any1;
    EXPECT_FALSE(any1.has_value());
    EXPECT_EQ(any1.type(), typeid(void));

    any1.emplace<bool>(true);
    EXPECT_TRUE(any1.has_value());
    EXPECT_EQ(any1.type(), typeid(bool));

    any1.emplace<std::string>();
    EXPECT_TRUE(any1.has_value());
    EXPECT_EQ(any1.type(), typeid(std::string));
}

TEST(
    any, NonMemberFunctions
)
{
    std::any any1(true);
    EXPECT_TRUE(any1.has_value());
    EXPECT_EQ(any1.type(), typeid(bool));

    EXPECT_THROW(std::any_cast<std::string>(any1), std::bad_any_cast);
    EXPECT_THROW(std::any_cast<double>(any1), std::bad_any_cast);
    EXPECT_THROW(std::any_cast<Sx>(any1), std::bad_any_cast);
    EXPECT_NO_THROW(std::any_cast<bool>(any1));
}

} // namespace
