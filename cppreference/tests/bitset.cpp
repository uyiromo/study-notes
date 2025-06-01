#include "gtest/gtest.h"
#include <bitset>

namespace
{
TEST(
    bitset, MemberFunctions
)
{
    constexpr std::size_t N = 8; // NOLINT

    // デフォルトコンストラクタ
    // 全ビットが 0
    auto b1 = std::bitset<8>(); // NOLINT
    EXPECT_EQ(b1.to_string(), "00000000");

    // unsigned long long からのコンストラクタ
    auto b2 = std::bitset<32>(0x80808080u); // NOLINT
    EXPECT_EQ(b2.to_string(), "10000000100000001000000010000000");

    // bitset のほうが小さい場合、下位ビットを採用
    auto b3 = std::bitset<8>(0x81828384u); // NOLINT
    EXPECT_EQ(b3.to_string(), "10000100");

    // bitset のほうが大きい場合、上位ビットを 0 にする
    auto b4 = std::bitset<32>(0x80u); // NOLINT
    EXPECT_EQ(b4.to_string(), "00000000000000000000000010000000");

    // std::string からのコンストラクタ
    const auto s1 = std::string("10000111011001010100001100100001"); // 0x87654321 NOLINT
    const auto s2 = std::string("ABABABAB");                         // NOLINT

    auto b5x = std::bitset<32>(s1);                                  // NOLINT    S1 全体
    auto b5y = std::bitset<16>(s1, 0z, 16z);                         // NOLINT    S1 上位 16-bit
    auto b5z = std::bitset<16>(s1, 16z, 16z);                        // NOLINT    S1 下位 16-bit
    EXPECT_EQ(b5x.to_string(), s1);
    EXPECT_EQ(b5y.to_string(), s1.substr(0, 16));
    EXPECT_EQ(b5z.to_string(), s1.substr(16, 32));

    // 'A' = 0, 'B' = 1 としてパース
    auto b6 = std::bitset<8>(s2, 0z, s2.npos, 'A', 'B'); // NOLINT    S1 下位 16-bit
    EXPECT_EQ(b6.to_string(), "01010101");
}

TEST(
    bitset, ElementAccess
)
{
    using bs_t = std::bitset<8>; // NOLINT
    auto b1 = bs_t(0b10101010);  // NOLINT
    auto b2 = bs_t(0b11111111);  // NOLINT
    auto b3 = bs_t(0b00000000);  // NOLINT

    static_assert(std::is_same_v<decltype(b1[0]), bs_t::reference>);
    static_assert(std::is_same_v<decltype(std::as_const(b1)[0]), bool>);

    // 0-bit は右端
    for (std::size_t i = 0; i < b1.size(); ++i)
    {
        if (i % 2 == 0)
        {
            EXPECT_FALSE(b1[i]);
        }
        else
        {
            EXPECT_TRUE(b1[i]);
        }
    }

    EXPECT_TRUE(b1.any());
    EXPECT_TRUE(b2.all());
    EXPECT_TRUE(b3.none());

    EXPECT_EQ(b1.count(), 4);
    EXPECT_EQ(b2.count(), 8);
    EXPECT_EQ(b3.count(), 0);

    // reference 経由で操作可能
    EXPECT_EQ(b1.to_string(), "10101010");
    b1[0] = true;
    b1[2].flip();
    EXPECT_EQ(b1.to_string(), "10101111");
}

TEST(
    bitset, Modifiers
)
{
    using bs_t = std::bitset<8>; // NOLINT
    auto b1 = bs_t(0b10101010);  // NOLINT
    auto b2 = bs_t(0b11010101);  // NOLINT

    b1 = bs_t(0b10101010);       // NOLINT
    b1 &= b2;                    // NOLINT
    EXPECT_EQ(b1.to_string(), "10000000");

    b1 = bs_t(0b10101010);       // NOLINT
    b1 |= b2;                    // NOLINT
    EXPECT_EQ(b1.to_string(), "11111111");

    b1 = bs_t(0b10101010);       // NOLINT
    b1 ^= b2;                    // NOLINT
    EXPECT_EQ(b1.to_string(), "01111111");

    auto b3 = ~b2;               // NOLINT
    EXPECT_EQ(b3.to_string(), "00101010");

    b1 = bs_t(0b10101010);       // NOLINT
    b1 <<= 2;                    // NOLINT
    EXPECT_EQ(b1.to_string(), "10101000");

    b1 = bs_t(0b10101010);       // NOLINT
    b1 >>= 2;                    // NOLINT
    EXPECT_EQ(b1.to_string(), "00101010");

    b1 = bs_t(0b10101010);       // NOLINT
    auto b4 = b1 << 2;           // NOLINT
    EXPECT_EQ(b4.to_string(), "10101000");

    b1 = bs_t(0b10101010);       // NOLINT
    auto b5 = b1 >> 2;           // NOLINT
    EXPECT_EQ(b5.to_string(), "00101010");

    b1 = bs_t(0b10101010);       // NOLINT
    b1.set();
    EXPECT_EQ(b1.to_string(), "11111111");

    b1 = bs_t(0b10101010); // NOLINT
    b1.set(1, false);      // NOLINT
    EXPECT_EQ(b1.to_string(), "10101000");

    b1.reset();
    EXPECT_EQ(b1.to_string(), "00000000");

    b1 = bs_t(0b10101010); // NOLINT
    b1.flip();
    EXPECT_EQ(b1.to_string(), "01010101");
}

} // namespace
