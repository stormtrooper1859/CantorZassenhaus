#include "gtest/gtest.h"

#include <string>
#include <set>
#include "CantorZassenhaus.h"
#include "Polynomial.h"


using namespace std;


bool check_answer(std::vector<std::pair<Polynomial, int>> expected, std::vector<std::pair<Polynomial, int>> result) {
    set<std::pair<Polynomial, int>> s1(expected.begin(), expected.end());
    set<std::pair<Polynomial, int>> s2(result.begin(), result.end());

    return s1 == s2;
};


TEST(CantorZassenhaus, simple) {
    Polynomial poly = Polynomial("1x^12+1x^11+2x^9+2x^8+2x^6+1x^5+2x^4+2x^3");

    std::vector<std::pair<Polynomial, int>> expected = {
        {Polynomial("1x^2+1x^1+2x^0"), 1},
        {Polynomial("1x^3+2x^1+1x^0"), 1},
        {Polynomial("1x^2+1x^0"), 2},
        {Polynomial("1x^1"), 3},
    };

    auto result = factor(poly, 3);

    EXPECT_TRUE(check_answer(expected, result));
}


TEST(CantorZassenhaus, simple_2) {
    Polynomial poly = Polynomial("1x^11+1x^10+1x^9+1x^8+1x^6+1x^5+1x^0");

    std::vector<std::pair<Polynomial, int>> expected = {
        {Polynomial("1x^3+1x^1+1x^0"), 1},
        {Polynomial("1x^2+1x^1+1x^0"), 1},
        {Polynomial("1x^3+1x^2+1x^0"), 2},
    };

    auto result = factor(poly, 2);

    EXPECT_TRUE(check_answer(expected, result));
}


TEST(CantorZassenhaus, equal_degree) {
    Polynomial poly = Polynomial("1x^24+10x^23+32x^22+28x^21+13x^20+13x^19+17x^18+12x^17+29x^16+16x^15+13x^14+30x^13+31x^12+31x^11+2x^10+15x^9+5x^8+15x^7+3x^6+10x^5+18x^4+4x^3+6x^2+36x^1+19x^0");

    std::vector<std::pair<Polynomial, int>> expected = {
        {Polynomial("1x^12+2x^11+30x^10+27x^9+23x^8+7x^7+4x^6+15x^5+8x^4+10x^3+16x^2+8x^1+15x^0"), 1},
        {Polynomial("1x^12+8x^11+23x^10+11x^9+24x^8+7x^7+25x^6+12x^5+30x^4+16x^3+34x^2+6x^1+21x^0"), 1},
    };

    auto result = factor(poly, 37);

    EXPECT_TRUE(check_answer(expected, result));
}


TEST(CantorZassenhaus, equal_degree_2) {
    Polynomial poly = Polynomial("1x^14+1x^10+1x^9+1x^8+1x^7+1x^6+1x^3+1x^2+1x^0");

    std::vector<std::pair<Polynomial, int>> expected = {
        {Polynomial("1x^7+1x^4+1x^0"), 1},
        {Polynomial("1x^7+1x^4+1x^3+1x^2+1x^0"), 1},
    };

    auto result = factor(poly, 2);

    EXPECT_TRUE(check_answer(expected, result));
}


TEST(CantorZassenhaus, many_output_2) {
    Polynomial poly = Polynomial("1x^63+1x^0");

    std::vector<std::pair<Polynomial, int>> expected = {
        {Polynomial("1x^1+1x^0"), 1},
        {Polynomial("1x^2+1x^1+1x^0"), 1},
        {Polynomial("1x^3+1x^2+1x^0"), 1},
        {Polynomial("1x^3+1x^1+1x^0"), 1},
        {Polynomial("1x^6+1x^4+1x^3+1x^1+1x^0"), 1},
        {Polynomial("1x^6+1x^5+1x^0"), 1},
        {Polynomial("1x^6+1x^5+1x^3+1x^2+1x^0"), 1},
        {Polynomial("1x^6+1x^5+1x^4+1x^1+1x^0"), 1},
        {Polynomial("1x^6+1x^4+1x^2+1x^1+1x^0"), 1},
        {Polynomial("1x^6+1x^3+1x^0"), 1},
        {Polynomial("1x^6+1x^1+1x^0"), 1},
        {Polynomial("1x^6+1x^5+1x^4+1x^2+1x^0"), 1},
        {Polynomial("1x^6+1x^5+1x^2+1x^1+1x^0"), 1},
    };

    auto result = factor(poly, 2);

    EXPECT_TRUE(check_answer(expected, result));
}
