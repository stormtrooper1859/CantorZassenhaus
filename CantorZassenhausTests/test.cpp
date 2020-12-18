#include "gtest/gtest.h"

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstdint>

#include <string>
#include "Polynomial.h"

TEST(Polynomial, div1) {
    Polynomial p1 = Polynomial({ 2, 1, 2, 2, 2, 0, 0, 2 });
    Polynomial p2 = Polynomial({ 2, 0, 1, 1 });

    Polynomial p3 = div(p1, p2, 3);

    std::string result = "x^4+2x^3+2x^2+x+2";

    EXPECT_EQ(p3.to_string(), result);
    EXPECT_TRUE(true);
}