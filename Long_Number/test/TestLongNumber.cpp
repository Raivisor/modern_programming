#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>

#include "LongNumber.hpp"

using namespace mogger;

// ----------------------------------------------------------
// CONSTRUCTORS
// ----------------------------------------------------------
TEST(LongNumberTest, DefaultConstructor) {
	LongNumber x;
    std::stringstream ss;
    ss << x;
    EXPECT_EQ(ss.str(), "0");
}

TEST(LongNumberTest, ConstructorFromInt) {
    LongNumber a(0);
    LongNumber b(15);
    //LongNumber c(-17);

    std::cerr << "Отработал" << std::endl;

    std::stringstream ss;
    ss << a;
    EXPECT_EQ(ss.str(), "0");

    ss.str("");
    ss << b;
    EXPECT_EQ(ss.str(), "15");

    // ss.str("");
    // ss << c;
    // EXPECT_EQ(ss.str(), "-17");
}

TEST(LongNumberTest, ConstructorWithLengthAndSign) {
    {
        LongNumber x1(2, 1);
        std::stringstream ss;
        ss << x1;
        EXPECT_EQ(ss.str(), "00") << "Ошибка";
    }
    {
        LongNumber x2(-5, 1);
        std::stringstream ss;
        ss << x2;
        EXPECT_EQ(ss.str(), "0");
    }
    {
        LongNumber x3(5, 2);
        std::stringstream ss;
        ss << x3;
        EXPECT_EQ(ss.str(), "00000");
    }
    {
        LongNumber x4(5, -3);
        std::stringstream ss;
        ss << x4;
        EXPECT_EQ(ss.str(), "00000");
    } 
}

TEST(LongNumberTest, ConstructorFromString) {
    {
        LongNumber x("12345");
        std::stringstream ss;
        ss << x;
        EXPECT_EQ(ss.str(), "12345");
    }
    {
        LongNumber x("-6789");
        std::stringstream ss;
        ss << x;
        EXPECT_EQ(ss.str(), "-6789");
    }
    {
        LongNumber x("0");
        std::stringstream ss;
        ss << x;
        EXPECT_EQ(ss.str(), "0");
    }
    {
        LongNumber x("");
        std::stringstream ss;
        ss << x;
        EXPECT_EQ(ss.str(), "0");
    }
    {
        LongNumber x("-");
        std::stringstream ss;
        ss << x;
        EXPECT_EQ(ss.str(), "0");
    }
    {
        LongNumber x("00123");
        std::stringstream ss;
        ss << x;
        EXPECT_EQ(ss.str(), "123");
    }
}

TEST(LongNumberTest, CopyConstructor) {
    LongNumber original("12345");
    LongNumber copy(original);
    
    std::stringstream ss;
    ss << copy;
    EXPECT_EQ(ss.str(), "12345");
    
    original = LongNumber("6789");
    ss.str("");
    ss << copy;
    EXPECT_EQ(ss.str(), "12345");
}

TEST(LongNumberTest, MoveConstructor) {
    LongNumber original("12345");
    LongNumber moved(std::move(original));
    
    std::stringstream ss;
    ss << moved;
    EXPECT_EQ(ss.str(), "12345");
    
    ss.str("");
    ss << original;
    EXPECT_EQ(ss.str(), "0");

    ss.str("");
    ss << moved;
    EXPECT_EQ(ss.str(), "12345");
}

// ----------------------------------------------------------
// ASSIGNMENT OPERATORS
// ----------------------------------------------------------
TEST(LongNumberTest, AssignFromString) {
    LongNumber x;
    x = "12345";
    
    std::stringstream ss;
    ss << x;
    EXPECT_EQ(ss.str(), "12345");
    
    x = "-6789";
    ss.str("");
    ss << x;
    EXPECT_EQ(ss.str(), "-6789");
    
    x = "0";
    ss.str("");
    ss << x;
    EXPECT_EQ(ss.str(), "0");
}

TEST(LongNumberTest, CopyAssignment) {
    LongNumber original("12345");
    LongNumber x;
    
    x = original;
    
    std::stringstream ss;
    ss << x;
    EXPECT_EQ(ss.str(), "12345");
    
    // Проверка независимости
    original = LongNumber("6789");
    ss.str("");
    ss << x;
    EXPECT_EQ(ss.str(), "12345");
    
    // Самоприсваивание
    x = x;
    ss.str("");
    ss << x;
    EXPECT_EQ(ss.str(), "12345");
}

TEST(LongNumberTest, MoveAssignment) {
    LongNumber original("12345");
    LongNumber x;
    
    x = std::move(original);
    
    std::stringstream ss;
    ss << x;
    EXPECT_EQ(ss.str(), "12345");
    
    ss.str("");
    ss << original;
    EXPECT_EQ(ss.str(), "0");
    
    // Самоперемещение
    x = std::move(x);
    ss.str("");
    ss << x;
    EXPECT_EQ(ss.str(), "12345");
}

// ----------------------------------------------------------
// COMPARE OPERATORS
// ----------------------------------------------------------
TEST(LongNumberTest, EqualityTest) {
    LongNumber a("12345");
    LongNumber b("54632");
    LongNumber c("12345");
    LongNumber d("-12345");

    EXPECT_TRUE(a == a);
    EXPECT_TRUE(d == d);
    EXPECT_TRUE(a == c);

    EXPECT_FALSE(a == b);
    EXPECT_FALSE(a == d);
}

TEST(LongNumberTest, InequalityTest) {
    LongNumber a("12345");
    LongNumber b("54632");
    LongNumber c("12345");
    LongNumber d("-12345");

    EXPECT_TRUE(a != b);
    EXPECT_TRUE(a != d);

    EXPECT_FALSE(a != c);
    EXPECT_FALSE(d != d);
    EXPECT_FALSE(a != a);
}

TEST(LongNumberTest, EqualityWithZero) {
    LongNumber zero1;
    LongNumber zero2("0");
    LongNumber zero3("-0");
    LongNumber positive("123");
    
    EXPECT_TRUE(zero1 == zero2);
    EXPECT_TRUE(zero1 == zero3);
    EXPECT_FALSE(zero1 == positive);
}

TEST(LongNumberTest, GreaterThanOperator) {
    LongNumber large("67");
    LongNumber medium("58");
    LongNumber small("-15");
    LongNumber extra_small("-67");

    EXPECT_TRUE(large > medium);
    EXPECT_TRUE(medium > small);
    EXPECT_TRUE(small > extra_small);

    EXPECT_FALSE(small > medium);
    EXPECT_FALSE(medium > large);
    EXPECT_FALSE(large > large);
    EXPECT_FALSE(small > small);
}

TEST(LongNumberTest, LessThanOperator) {
    LongNumber large("67");
    LongNumber medium("58");
    LongNumber small("-15");
    LongNumber extra_small("-567");

    EXPECT_TRUE(medium < large);
    EXPECT_TRUE(small < large);
    EXPECT_TRUE(extra_small < small);

    EXPECT_FALSE(medium < small);
    EXPECT_FALSE(large < medium);
    EXPECT_FALSE(small < extra_small);
}

TEST(LongNumberTest, CaseWithZero) {
    LongNumber zero_pos;
    LongNumber zero_neg("-0");
    LongNumber pos("67");
    LongNumber neg("-67");

    EXPECT_TRUE(pos > zero_pos);
    EXPECT_TRUE(pos > zero_neg);
    EXPECT_TRUE(neg < zero_pos);
    EXPECT_TRUE(neg < zero_neg);
    EXPECT_TRUE(zero_pos == zero_neg);
    EXPECT_FALSE(zero_pos > zero_neg);
}

TEST(LongNumberTest, CompareDifferentLength) {
    LongNumber long_num("2718281828");
    LongNumber short_num("67");
    LongNumber neg("-1");
    LongNumber extra_neg("-67");

    EXPECT_TRUE(short_num != long_num);
    EXPECT_TRUE(short_num != neg);

    EXPECT_FALSE(short_num == long_num);
    EXPECT_FALSE(neg == short_num);

    EXPECT_TRUE(long_num > short_num);
    EXPECT_TRUE(neg > extra_neg);
    EXPECT_FALSE(short_num > long_num);

    EXPECT_TRUE(short_num < long_num);
    EXPECT_TRUE(neg < short_num);
    EXPECT_TRUE(extra_neg < neg);

    EXPECT_FALSE(long_num < short_num);
    EXPECT_FALSE(short_num < neg);
}

// ----------------------------------------------------------
// ARITHMETIC OPERATORS
// ----------------------------------------------------------
TEST(LongNumberAdditionTest, SameSignPositive) {
    LongNumber a("123");
    LongNumber b("456");
    LongNumber result = a + b;
    
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "579");
}

TEST(LongNumberAdditionTest, SameSignNegative) {
    LongNumber a("-123");
    LongNumber b("-456");
    LongNumber result = a + b;
    
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "-579");
}

TEST(LongNumberAdditionTest, DifferentSignFirstPositive) {
    LongNumber a("500");
    LongNumber b("-123");
    LongNumber result = a + b;
    
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "377");
}

TEST(LongNumberAdditionTest, DifferentSignFirstNegative) {
    LongNumber a("-500");
    LongNumber b("123");
    LongNumber result = a + b;
    
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "-377");
}

TEST(LongNumberAdditionTest, DifferentSignEqualAbsolute) {
    LongNumber a("123");
    LongNumber b("-123");
    LongNumber result = a + b;
    
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "0");
    
    LongNumber c("-456");
    LongNumber d("456");
    result = c + d;
    
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "0");
}

TEST(LongNumberAdditionTest, WithZero) {
    LongNumber zero;
    LongNumber positive("123");
    LongNumber negative("-456");
    
    LongNumber result = positive + zero;
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "123");
    
    result = negative + zero;
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "-456");
    
    result = zero + positive;
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "123");
    
    result = zero + negative;
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "-456");
    
    result = zero + zero;
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "0");
}

TEST(LongNumberAdditionTest, WithCarry) {
    LongNumber a("999");
    LongNumber b("1");
    LongNumber result = a + b;
    
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "1000");
    
    LongNumber c("-999");
    LongNumber d("-1");
    result = c + d;
    
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "-1000");
    
    LongNumber e("999");
    LongNumber f("-1");
    result = e + f;
    
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "998");
}

TEST(LongNumberAdditionTest, DifferentLength) {
    LongNumber a("1000");
    LongNumber b("1");
    LongNumber result = a + b;
    
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "1001");
    
    LongNumber c("9999");
    LongNumber d("1");
    result = c + d;
    
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "10000");
    
    LongNumber e("-1000");
    LongNumber f("-1");
    result = e + f;
    
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "-1001");
}

TEST(LongNumberSubtractionTest, SameSignPositive) {
    LongNumber a("456");
    LongNumber b("123");
    LongNumber result = a - b;
    
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "333");
}

TEST(LongNumberSubtractionTest, SameSignNegative) {
    LongNumber a("-123");
    LongNumber b("-456");
    LongNumber result = a - b;
    
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "333");
    
    LongNumber c("-456");
    LongNumber d("-123");
    result = c - d;
    
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "-333");
}

TEST(LongNumberSubtractionTest, DifferentSignFirstPositive) {
    LongNumber a("500");
    LongNumber b("-123");
    LongNumber result = a - b;
    
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "623");
}

TEST(LongNumberSubtractionTest, DifferentSignFirstNegative) {
    LongNumber a("-500");
    LongNumber b("123");
    LongNumber result = a - b;
    
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "-623");
    
    LongNumber c("-500");
    LongNumber d("-123");
}

TEST(LongNumberSubtractionTest, ResultZero) {
    LongNumber a("123");
    LongNumber b("123");
    LongNumber result = a - b;
    
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "0");
    
    LongNumber c("-456");
    LongNumber d("-456");
    result = c - d;
    
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "0");
}

TEST(LongNumberSubtractionTest, WithZero) {
    LongNumber zero;
    LongNumber positive("123");
    LongNumber negative("-456");
    
    LongNumber result = positive - zero;
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "123");
    
    result = negative - zero;
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "-456");

    result = zero - positive;
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "-123");

    result = zero - negative;
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "456");
}

TEST(LongNumberSubtractionTest, WithBorrow) {
    LongNumber a("1000");
    LongNumber b("1");
    LongNumber result = a - b;
    
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "999");
    
    LongNumber c("1000");
    LongNumber d("999");
    result = c - d;
    
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "1");
    
    LongNumber e("-1000");
    LongNumber f("1");
    result = e - f;
    
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "-1001");
}

TEST(LongNumberSubtractionTest, DifferentLength) {
    LongNumber a("1000");
    LongNumber b("999");
    LongNumber result = a - b;
    
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "1");
    
    LongNumber c("10000");
    LongNumber d("1");
    result = c - d;
    
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "9999");
}

TEST(LongNumberMultiplicationTest, Basic) {
    LongNumber a("123");
    LongNumber b("45");
    LongNumber result = a * b;
    
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "5535");
}

TEST(LongNumberMultiplicationTest, Large) {
    LongNumber a("999");
    LongNumber b("999");
    LongNumber result = a * b;
    
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "998001");
}

TEST(LongNumberMultiplicationTest, WithZero) {
    LongNumber zero;
    LongNumber positive("123");
    LongNumber negative("-456");
    
    LongNumber result = positive * zero;
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "0");
    
    result = negative * zero;
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "0");
    
    result = zero * positive;
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "0");
    
    result = zero * zero;
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "0");
}

TEST(LongNumberMultiplicationTest, NegativeNumbers) {
    LongNumber a("-123");
    LongNumber b("45");
    LongNumber c("-45");
    
    LongNumber result = a * b;
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "-5535");
    
    result = a * c;
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "5535");
    
    result = b * a;
    ss.str("");
    ss << result;
    EXPECT_EQ(ss.str(), "-5535");
}

TEST(LongNumberMultiplicationTest, MixedSignsAndZero) {
    LongNumber positive("123");
    LongNumber negative("-123");
    LongNumber zero;
    
    EXPECT_FALSE((positive * negative).is_zero());
    EXPECT_TRUE((positive * negative).is_negative());
    
    EXPECT_TRUE((negative * positive).is_negative());
    
    EXPECT_TRUE((zero * negative).is_zero());
    EXPECT_FALSE((zero * negative).is_negative());
}

TEST(LongNumberDivisionTest, SimplePositive) {
    LongNumber a("12345");
    LongNumber b("45");
    
    LongNumber quotient = a / b;
    LongNumber remainder = a % b;
    std::stringstream ss;
    ss << quotient;
    EXPECT_EQ(ss.str(), "274");
    
    ss.str("");
    ss << remainder;
    EXPECT_EQ(ss.str(), "15");
}

TEST(LongNumberDivisionTest, ExactDivision) {
    LongNumber a("12345");
    LongNumber b("5");
    
    LongNumber quotient = a / b;
    LongNumber remainder = a % b;
    
    std::stringstream ss;
    ss << quotient;
    EXPECT_EQ(ss.str(), "2469");
    EXPECT_TRUE(remainder.is_zero());
}

TEST(LongNumberDivisionTest, DividendLessThanDivisor) {
    LongNumber a("123");
    LongNumber b("456");
    
    LongNumber quotient = a / b;
    LongNumber remainder = a % b;
    
    std::stringstream ss;
    ss << quotient;
    EXPECT_EQ(ss.str(), "0");
    
    ss.str("");
    ss << remainder;
    EXPECT_EQ(ss.str(), "123");
}

TEST(LongNumberDivisionTest, EqualNumbers) {
    LongNumber a("12345");
    LongNumber b("12345");
    
    LongNumber quotient = a / b;
    LongNumber remainder = a % b;
    
    std::stringstream ss;
    ss << quotient;
    EXPECT_EQ(ss.str(), "1");
    EXPECT_TRUE(remainder.is_zero());
}

TEST(LongNumberDivisionTest, WithZero) {
    LongNumber zero;
    LongNumber positive("12345");
    
    EXPECT_THROW(positive / zero, std::runtime_error);
    
    LongNumber quotient = zero / positive;
    std::stringstream ss;
    ss << quotient;
    EXPECT_EQ(ss.str(), "0");
}

TEST(LongNumberDivisionTest, NegativeNumbers) {
    LongNumber a("-12345");
    LongNumber b("45");
    LongNumber c("-45");
    
    std::stringstream ss;
    ss << (a / b);
    EXPECT_EQ(ss.str(), "-274");
    
    ss.str("");
    ss << (a / c);
    EXPECT_EQ(ss.str(), "274");
}

TEST(LongNumberDivisionTest, LargeNumber) {
    LongNumber a("12345678901234567890");
    LongNumber b("12345");
    
    LongNumber quotient = a / b;
    std::stringstream ss;
    ss << quotient;
    EXPECT_EQ(ss.str(), "1000054994024671");
}

TEST(LongNumberDivisionTest, PowersOfTen) {
    LongNumber a("1000000");
    LongNumber b("10");
    
    std::stringstream ss;
    ss << (a / b);
    EXPECT_EQ(ss.str(), "100000");
}
 
int main(int argc,char **argv){
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}