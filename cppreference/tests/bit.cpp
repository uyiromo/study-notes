#include "gtest/gtest.h"
#include <bit>
#include <cstddef>

namespace
{
TEST(
    bit, bit_cast
)
{
    //
    // sign: 0
    // exponent: 011'1111'1110
    // mantissa: 1001'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000
    constexpr double        d1 = 0.781250;                         // NOLINT
    constexpr std::uint64_t u1 = std::bit_cast<std::uint64_t>(d1); // NOLINT
    static_assert(u1 == 0x3FE9'0000'0000'0000ul);                  // NOLINT
}

TEST(
    bit, byteswap
)
{
    constexpr std::uint16_t u16 = 0xABCD;                           // NOLINT
    constexpr std::uint32_t u32 = 0xABCD'EF01;                      // NOLINT
    constexpr std::uint64_t u64 = 0xABCD'EF01'2345'6789;            // NOLINT
    static_assert(std::byteswap(u16) == 0xCDAB);                    // NOLINT
    static_assert(std::byteswap(u32) == 0x01EF'CDAB);               // NOLINT
    static_assert(std::byteswap(u64) == 0x89'67'45'23'01'EF'CD'AB); // NOLINT
}

TEST(
    bit, integral
)
{
    EXPECT_FALSE(std::has_single_bit(0b0000u));  // NOLINT
    EXPECT_TRUE(std::has_single_bit(0b0100u));   // NOLINT
    EXPECT_FALSE(std::has_single_bit(0b0110u));  // NOLINT

    EXPECT_EQ(0b0100u, std::bit_ceil(0b0100u));  // NOLINT
    EXPECT_EQ(0b1000u, std::bit_ceil(0b0110u));  // NOLINT

    EXPECT_EQ(0b0100u, std::bit_floor(0b0100u)); // NOLINT
    EXPECT_EQ(0b0100u, std::bit_floor(0b0110u)); // NOLINT

    EXPECT_EQ(0, std::bit_width(0b0000u));       // NOLINT
    EXPECT_EQ(3, std::bit_width(0b0100u));       // NOLINT
    EXPECT_EQ(3, std::bit_width(0b0110u));       // NOLINT
}

TEST(
    bit, rotating
)
{
    // suffix "u" は unsigned int なので rotl(3) は巡回シフトが発生しない
    EXPECT_EQ(0b110000100000u, std::rotl(0b000110000100u, 3));                 // NOLINT
    EXPECT_EQ(0x8000'0000u | 0b000000110000u, std::rotl(0b000110000100u, -3)); // NOLINT

    EXPECT_EQ(0x8000'0000u | 0b000000110000u, std::rotr(0b000110000100u, 3));  // NOLINT
    EXPECT_EQ(0b110000100000u, std::rotr(0b000110000100u, -3));                // NOLINT
}

TEST(
    bit, counting
)
{
    EXPECT_EQ(3, std::countl_zero(0x1000'0000u)); // NOLINT
    EXPECT_EQ(0, std::countl_zero(0x8000'0000u)); // NOLINT

    EXPECT_EQ(4, std::countl_one(0xF000'0000u));  // NOLINT
    EXPECT_EQ(0, std::countl_one(0x7000'0000u));  // NOLINT

    EXPECT_EQ(3, std::countr_zero(0x0000'0008u)); // NOLINT
    EXPECT_EQ(0, std::countr_zero(0x0000'0001u)); // NOLINT

    EXPECT_EQ(3, std::countr_one(0x0000'0007u));  // NOLINT
    EXPECT_EQ(0, std::countr_one(0x0000'0008u));  // NOLINT

    EXPECT_EQ(4, std::popcount(0x8080'8080u));    // NOLINT
}

} // namespace
