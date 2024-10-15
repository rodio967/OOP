#include <gtest/gtest.h>
#include "BitArray.h"


TEST(BitArrayTest, DefaultConstructor) {
    BitArray bits;
    EXPECT_EQ(bits.size(), 0);
    EXPECT_TRUE(bits.empty());
    EXPECT_FALSE(bits.any());
    EXPECT_TRUE(bits.none());
    EXPECT_EQ(bits.to_string(), "");
}

TEST(BitArrayTest, ParameterizedConstructor) {
    BitArray bits1(16, 0xFF);
    EXPECT_EQ(bits1.size(), 16);
    EXPECT_FALSE(bits1.empty());
    EXPECT_TRUE(bits1.any());
    EXPECT_FALSE(bits1.none());
    EXPECT_EQ(bits1.count(), 8);
    EXPECT_EQ(bits1.to_string(), "0000000011111111");

    BitArray bits2(0);
    EXPECT_EQ(bits2.size(), 0);
    EXPECT_TRUE(bits2.empty());
}

TEST(BitArrayTest, CopyConstructor) {
    BitArray original(16, 0xFF);
    BitArray copy(original);
    EXPECT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy.to_string(), original.to_string());

    copy.reset(0);
    EXPECT_EQ(copy[0], false);
    EXPECT_EQ(original[0], true);
}

TEST(BitArrayTest, AssignmentOperator) {
    BitArray bits1(16, 0xFF);
    BitArray bits2(16);
    bits2 = bits1;
    EXPECT_EQ(bits2.size(), bits1.size());
    EXPECT_EQ(bits2.to_string(), bits1.to_string());

    bits2 = bits2;
    EXPECT_EQ(bits2.to_string(), bits1.to_string());

    bits2.reset(0);
    EXPECT_EQ(bits2[0], false);
    EXPECT_EQ(bits1[0], true);
}

TEST(BitArrayTest, SwapMethod) {
    BitArray bits1(8, 0xAA);
    BitArray bits2(8, 0x55);

    bits1.swap(bits2);

    EXPECT_EQ(bits1.to_string(), "01010101");
    EXPECT_EQ(bits2.to_string(), "10101010");
}

TEST(BitArrayTest, ResizeMethod) {
    BitArray bits(8, 0xFF);
    bits.resize(16, false);
    EXPECT_EQ(bits.size(), 16);
    EXPECT_EQ(bits.to_string(), "0000000011111111");

    bits.resize(4);
    EXPECT_EQ(bits.size(), 4);
    EXPECT_EQ(bits.to_string(), "1111");

    bits.resize(8, true);
    EXPECT_EQ(bits.size(), 8);
    EXPECT_EQ(bits.to_string(), "11111111");
}

TEST(BitArrayTest, ClearMethod) {
    BitArray bits(16, 0xFF);
    bits.clear();
    EXPECT_EQ(bits.size(), 0);
    EXPECT_TRUE(bits.empty());
    EXPECT_FALSE(bits.any());
    EXPECT_TRUE(bits.none());
    EXPECT_EQ(bits.to_string(), "");
}

TEST(BitArrayTest, PushBackMethod) {
    BitArray bits;
    bits.push_back(true);
    bits.push_back(false);
    bits.push_back(true);
    EXPECT_EQ(bits.size(), 3);
    EXPECT_EQ(bits.to_string(), "101");
    EXPECT_TRUE(bits[0]);
    EXPECT_FALSE(bits[1]);
    EXPECT_TRUE(bits[2]);
}

TEST(BitArrayTest, BitwiseOperators) {
    BitArray bits1(8, 0b10101010);
    BitArray bits2(8, 0b11001100);

    BitArray expected_and(8, 0b10001000);
    BitArray and_result = bits1;
    and_result &= bits2;
    EXPECT_EQ(and_result.to_string(), expected_and.to_string());

    BitArray expected_or(8, 0b11101110);
    BitArray or_result = bits1;
    or_result |= bits2;
    EXPECT_EQ(or_result.to_string(), expected_or.to_string());

    BitArray expected_xor(8, 0b01100110);
    BitArray xor_result = bits1;
    xor_result ^= bits2;
    EXPECT_EQ(xor_result.to_string(), expected_xor.to_string());
}

TEST(BitArrayTest, BitShiftOperators) {
    BitArray bits(16, 0x0F0F);

    BitArray shifted_left_expected(16, 0xF0F0);
    BitArray shifted_left = bits;
    shifted_left <<= 4;
    EXPECT_EQ(shifted_left.to_string(), shifted_left_expected.to_string());

    BitArray shifted_right_expected(16, 0x000F);
    BitArray shifted_right = bits;
    shifted_right >>= 8;
    EXPECT_EQ(shifted_right.to_string(), shifted_right_expected.to_string());
}

TEST(BitArrayTest, SetMethod) {
    BitArray bits(8, 0x00);
    bits.set(0, true);
    bits.set(7, true);
    bits.set(3, true);
    EXPECT_EQ(bits.to_string(), "10001001");

    bits.set(3, false);
    EXPECT_EQ(bits.to_string(), "10000001");
}

TEST(BitArrayTest, SetAllMethod) {
    BitArray bits(8, 0x00);
    bits.set();
    EXPECT_EQ(bits.to_string(), "11111111");
}

TEST(BitArrayTest, ResetMethod) {
    BitArray bits(8, 0xFF);
    bits.reset(0);
    bits.reset(7);
    EXPECT_EQ(bits.to_string(), "01111110");
}

TEST(BitArrayTest, ResetAllMethod) {
    BitArray bits(8, 0xFF);
    bits.reset();
    EXPECT_EQ(bits.to_string(), "00000000");
}

TEST(BitArrayTest, AnyNoneMethods) {
    BitArray bits1(8, 0x00);
    EXPECT_FALSE(bits1.any());
    EXPECT_TRUE(bits1.none());

    BitArray bits2(8, 0x01);
    EXPECT_TRUE(bits2.any());
    EXPECT_FALSE(bits2.none());
}

TEST(BitArrayTest, BitwiseNotOperator) {
    BitArray bits(8, 0b10101010);
    BitArray inverted = ~bits;
    EXPECT_EQ(inverted.to_string(), "01010101");
}

TEST(BitArrayTest, CountMethod) {
    BitArray bits(8, 0xAA);
    EXPECT_EQ(bits.count(), 4);

    bits.set(0);
    EXPECT_EQ(bits.count(), 5);

    bits.reset();
    EXPECT_EQ(bits.count(), 0);
}

TEST(BitArrayTest, SubscriptOperator) {
    BitArray bits(8, 0x00);
    bits.set(0);
    bits.set(7);
    EXPECT_TRUE(bits[0]);
    EXPECT_FALSE(bits[1]);
    EXPECT_FALSE(bits[6]);
    EXPECT_TRUE(bits[7]);

    EXPECT_THROW(bits[8], std::out_of_range);
    EXPECT_THROW(bits[-1], std::out_of_range);
}

TEST(BitArrayTest, SizeMethod) {
    BitArray bits1;
    EXPECT_EQ(bits1.size(), 0);

    BitArray bits2(10);
    EXPECT_EQ(bits2.size(), 10);
}

TEST(BitArrayTest, EmptyMethod) {
    BitArray bits1;
    EXPECT_TRUE(bits1.empty());

    BitArray bits2(5);
    EXPECT_FALSE(bits2.empty());
}

TEST(BitArrayTest, ToStringMethod) {
    BitArray bits1(4, 0x0F);
    EXPECT_EQ(bits1.to_string(), "1111");

    BitArray bits2(8, 0xA5);
    EXPECT_EQ(bits2.to_string(), "10100101");

    BitArray bits3;
    EXPECT_EQ(bits3.to_string(), "");
}

TEST(BitArrayTest, ComparisonOperators) {
    BitArray bits1(8, 0xFF);
    BitArray bits2(8, 0xFF);
    BitArray bits3(8, 0x00);
    BitArray bits4(16, 0xFFFF);

    EXPECT_TRUE(bits1 == bits2);
    EXPECT_FALSE(bits1 == bits3);
    EXPECT_TRUE(bits1 != bits3);
    EXPECT_FALSE(bits1 != bits2);
    EXPECT_FALSE(bits1 == bits4);
}

TEST(BitArrayTest, ExternalBitwiseOperators) {
    BitArray bits1(8, 0b10101010);
    BitArray bits2(8, 0b11001100);

    BitArray expected_and(8, 0b10001000);
    BitArray and_result = bits1 & bits2;
    EXPECT_EQ(and_result.to_string(), expected_and.to_string());

    BitArray expected_or(8, 0b11101110);
    BitArray or_result = bits1 | bits2;
    EXPECT_EQ(or_result.to_string(), expected_or.to_string());

    BitArray expected_xor(8, 0b01100110);
    BitArray xor_result = bits1 ^ bits2;
    EXPECT_EQ(xor_result.to_string(), expected_xor.to_string());

    BitArray bits3(16, 0xFFFF);
    EXPECT_THROW(bits1 & bits3, std::invalid_argument);
    EXPECT_THROW(bits1 | bits3, std::invalid_argument);
    EXPECT_THROW(bits1 ^ bits3, std::invalid_argument);
}
