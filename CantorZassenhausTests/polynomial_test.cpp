#include "gtest/gtest.h"

#include <string>
#include "Polynomial.h"


TEST(Polynomial, to_string) {
    Polynomial p1 = Polynomial("2x^5+3x^4+x^2+2");

    std::string result = "2x^5+3x^4+x^2+2";

    EXPECT_EQ(p1.to_string(), result);
}

TEST(Polynomial, div1) {
    Polynomial p1 = Polynomial("2x^7+x^6+2x^5+2x^4+2x^3+2");
    Polynomial p2 = Polynomial("2x^3+x+1");

    auto p3div = Polynomial::div(p1, p2, 3);

    std::string result = "x^4+2x^3+2x^2+x+2";

    EXPECT_EQ(p3div.to_string(), result);
}

TEST(Polynomial, div2) {
    Polynomial p1 = Polynomial("x^5+x^3+2");
    Polynomial p2 = Polynomial("x+1");

    auto p3div = Polynomial::div(p1, p2, 3);

    std::string result = "x^4+2x^3+2x^2+x+2";

    EXPECT_EQ(p3div.to_string(), result);
}

TEST(Polynomial, add1) {
    Polynomial p1 = Polynomial("x^5+x^3+2");
    Polynomial p2 = Polynomial("x+1");

    auto p3 = Polynomial::add(p1, p2, 3);

    std::string result = "x^5+x^3+x";

    EXPECT_EQ(p3.to_string(), result);
}

TEST(Polynomial, add2) {
    Polynomial p1 = Polynomial("x^3+4x^2+6x+3");
    Polynomial p2 = Polynomial("6x^3+3x^2+2x+1");

    auto p3 = Polynomial::add(p1, p2, 7);

    std::string result = "x+4";

    EXPECT_EQ(p3.to_string(), result);
}

TEST(Polynomial, sub1) {
    Polynomial p1 = Polynomial("x^3+4x^2+6x+3");
    Polynomial p2 = Polynomial("x^3+4x^2+2x+1");

    auto p3 = Polynomial::sub(p1, p2, 7);

    std::string result = "4x+2";

    EXPECT_EQ(p3.to_string(), result);
}

TEST(Polynomial, mul1) {
    Polynomial p1 = Polynomial("2x^3+x^2+3x+1");
    Polynomial p2 = Polynomial("4x^2+x+2");

    auto p3 = Polynomial::mul(p1, p2, 5);

    std::string result = "3x^5+x^4+2x^3+4x^2+2x+2";

    EXPECT_EQ(p3.to_string(), result);
}

TEST(Polynomial, mul2) {
    Polynomial p1 = Polynomial("2x^57+x^48+3x+4");
    Polynomial p2 = Polynomial("4x^2+x+2");

    auto p3 = Polynomial::mul(p1, p2, 5);

    std::string result = "3x^59+2x^58+4x^57+4x^50+x^49+2x^48+2x^3+4x^2+3";

    EXPECT_EQ(p3.to_string(), result);
}

TEST(Polynomial, div_and_mod) {
    Polynomial p1 = Polynomial("x^2+1");
    Polynomial p2 = Polynomial("1");

    auto rm = Polynomial::mod(p2, p1, 3);
    auto rd = Polynomial::div(p2, p1, 3);

    std::string em = "1";
    std::string ed = "0";

    EXPECT_EQ(rm.to_string(), em);
    EXPECT_EQ(rd.to_string(), ed);
}

TEST(Polynomial, gcd1) {
    Polynomial p1 = Polynomial("2x^7+x^6+2x^5+2x^4+2x^3+2");
    Polynomial p2 = Polynomial("x^5+x^3+2");

    auto result = gcd(p1, p2, 3);

    std::string expected = "x^4+2x^3+2x^2+x+2";

    EXPECT_EQ(result.to_string(), expected);
}
