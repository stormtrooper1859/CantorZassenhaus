#include "gtest/gtest.h"

#include <string>
#include "Polynomial.h"


TEST(Polynomial, to_string) {
    Polynomial p1 = parse_polynomial("2x^5+3x^4+1x^2+2x^0");

    std::string result = "2x^5+3x^4+x^2+2";

    EXPECT_EQ(p1.to_string(), result);
}

TEST(Polynomial, div1) {
    Polynomial p1 = parse_polynomial("2x^7+1x^6+2x^5+2x^4+2x^3+2x^0");
    Polynomial p2 = parse_polynomial("2x^3+1x^1+1x^0");

    auto p3div = Polynomial::div(p1, p2, 3);

    std::string result = "x^4+2x^3+2x^2+x+2";

    EXPECT_EQ(p3div.to_string(), result);
}

TEST(Polynomial, div2) {
    Polynomial p1 = parse_polynomial("1x^5+1x^3+2x^0");
    Polynomial p2 = parse_polynomial("1x^1+1x^0");

    auto p3div = Polynomial::div(p1, p2, 3);

    std::string result = "x^4+2x^3+2x^2+x+2";

    EXPECT_EQ(p3div.to_string(), result);
}

TEST(Polynomial, add1) {
    Polynomial p1 = parse_polynomial("1x^5+1x^3+2x^0");
    Polynomial p2 = parse_polynomial("1x^1+1x^0");

    auto p3 = Polynomial::add(p1, p2, 3);

    std::string result = "x^5+x^3+x";

    EXPECT_EQ(p3.to_string(), result);
}

TEST(Polynomial, add2) {
    Polynomial p1 = parse_polynomial("1x^3+4x^2+6x^1+3x^0");
    Polynomial p2 = parse_polynomial("6x^3+3x^2+2x^1+1x^0");

    auto p3 = Polynomial::add(p1, p2, 7);

    std::string result = "x+4";

    EXPECT_EQ(p3.to_string(), result);
}

TEST(Polynomial, sub1) {
    Polynomial p1 = parse_polynomial("1x^3+4x^2+6x^1+3x^0");
    Polynomial p2 = parse_polynomial("1x^3+4x^2+2x^1+1x^0");

    auto p3 = Polynomial::sub(p1, p2, 7);

    std::string result = "4x+2";

    EXPECT_EQ(p3.to_string(), result);
}

TEST(Polynomial, mul1) {
    Polynomial p1 = parse_polynomial("2x^3+1x^2+3x^1+1x^0");
    Polynomial p2 = parse_polynomial("4x^2+1x^1+2x^0");

    auto p3 = Polynomial::mul(p1, p2, 5);

    std::string result = "3x^5+x^4+2x^3+4x^2+2x+2";

    EXPECT_EQ(p3.to_string(), result);
}

TEST(Polynomial, mul2) {
    Polynomial p1 = parse_polynomial("2x^57+1x^48+3x^1+4x^0");
    Polynomial p2 = parse_polynomial("4x^2+1x^1+2x^0");

    auto p3 = Polynomial::mul(p1, p2, 5);

    std::string result = "3x^59+2x^58+4x^57+4x^50+x^49+2x^48+2x^3+4x^2+3";

    EXPECT_EQ(p3.to_string(), result);
}
