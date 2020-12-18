#include "gtest/gtest.h"

#include <string>
#include "Polynomial.h"

TEST(Polynomial, to_string) {
    Polynomial p1 = Polynomial({ 2, 3, 0, 1, 0, 2 });

    std::string result = "2x^5+3x^4+x^2+2";

    EXPECT_EQ(p1.to_string(), result);
}

TEST(Polynomial, div1) {
    Polynomial p1 = Polynomial({ 2, 1, 2, 2, 2, 0, 0, 2 });
    Polynomial p2 = Polynomial({ 2, 0, 1, 1 });

    auto p3div = div(p1, p2, 3);

    std::string result = "x^4+2x^3+2x^2+x+2";

    EXPECT_EQ(p3div.first.to_string(), result);
}

TEST(Polynomial, div2) {
    Polynomial p1 = Polynomial({ 1, 0, 1, 0, 0, 2 });
    Polynomial p2 = Polynomial({ 1, 1 });

    auto p3div = div(p1, p2, 3);

    std::string result = "x^4+2x^3+2x^2+x+2";

    EXPECT_EQ(p3div.first.to_string(), result);
}

TEST(Polynomial, add1) {
    Polynomial p1 = Polynomial({ 1, 0, 1, 0, 0, 2 });
    Polynomial p2 = Polynomial({ 1, 1 });

    auto p3 = add(p1, p2, 3);

    std::string result = "x^5+x^3+x";

    EXPECT_EQ(p3.to_string(), result);
}

TEST(Polynomial, add2) {
    Polynomial p1 = Polynomial({ 1, 4, 6, 3 });
    Polynomial p2 = Polynomial({ 6, 3, 2, 1 });

    auto p3 = add(p1, p2, 7);

    std::string result = "x+4";

    EXPECT_EQ(p3.to_string(), result);
}

TEST(Polynomial, sub1) {
    Polynomial p1 = Polynomial({ 1, 4, 6, 3 });
    Polynomial p2 = Polynomial({ 1, 4, 2, 1 });

    auto p3 = sub(p1, p2, 7);

    std::string result = "4x+2";

    EXPECT_EQ(p3.to_string(), result);
}

TEST(Polynomial, mul1) {
    Polynomial p1 = Polynomial({ 2, 1, 3, 1 });
    Polynomial p2 = Polynomial({ 4, 1, 2 });

    auto p3 = mul(p1, p2, 5);

    std::string result = "3x^5+x^4+2x^3+4x^2+2x+2";

    EXPECT_EQ(p3.to_string(), result);
}
