#include "CantorZassenhaus.h"

#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

Polynomial get_random_polynomial(int max_degree, int modq) {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    uniform_int_distribution<int> dist(0, modq - 1);
    uniform_int_distribution<int> dist_degree(0, max_degree - 1);

    auto degree = dist_degree(rng) + 1;
    
    std::vector<int64_t> vr(degree + 1);
    vr[0] = 1;

    for (size_t i = 1; i < degree + 1; i++)
    {
        vr[i] = dist(rng);
    }

    Polynomial result(vr);

    return result;
}






using resultT = std::vector<std::pair<Polynomial, int>>;

resultT square_free_decomposition(Polynomial poly, int modp) {
    std::vector<std::pair<Polynomial, int>> result;

    Polynomial a = poly;
    int m = 1;
    
    Polynomial c;

    do {
        auto ad = a.diff(modp);
        c = gcd(a, ad, modp);
        auto w = Polynomial::div(a, c, modp).first;
        int i = 1;
        while (w != Polynomial({ 1 })) {
            auto y = gcd(w, c, modp);
            auto qq = Polynomial::div(w, y, modp).first;
            if (qq != Polynomial({ 1 })) {
                result.push_back({ qq, i * m });
            }
            w = y;
            c = Polynomial::div(c, y, modp).first;
            i++;
        }
        if (c != Polynomial({ 1 })) {
            a = c.zip(modp);
            m = m * modp;
        }
    } while (c != Polynomial({1}));

	return result;
}






vector<pair<Polynomial, int>> distinct_degree_factorization(Polynomial poly, int modp) {
    vector<pair<Polynomial, int>> result;

    auto ff = poly;
    Polynomial h({ 0, 1 });
    int i = 1;
    while (ff != Polynomial({ 1 })) {
        h = powmod(h, modp, poly, modp);
        auto sbs = Polynomial::sub(h, Polynomial({ 0, 1 }), modp);
        auto g = gcd(sbs, ff, modp);
        if (g != Polynomial({ 1 })) {
            result.push_back({ g, i });
            ff = Polynomial::div(ff, g, modp).first;
        }
        i++;
    }

    return result;
}


vector<Polynomial> equal_degree_factorization(Polynomial poly, int degree, int modp) {
	return vector<Polynomial>();
}



vector<Polynomial> factor_square_free(Polynomial poly, int modp) {
	return vector<Polynomial>();
}



resultT factor(Polynomial poly, int modp) {
	resultT result();

	resultT sqrfree = square_free_decomposition(poly, modp);
	
	for (auto const& value : sqrfree) {
		
	}



	return std::vector<std::pair<Polynomial, int>>();
}
