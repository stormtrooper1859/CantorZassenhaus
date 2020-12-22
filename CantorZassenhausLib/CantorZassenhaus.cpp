#include "CantorZassenhaus.h"

#include <algorithm>
#include <chrono>
#include <random>
#include <cassert>

using namespace std;

// include max_degree
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
    if (poly.get_degree() == degree) {
        return vector<Polynomial>({ poly });
    }

	vector<Polynomial> result;

    Polynomial g({ 1 });

    while (g == Polynomial({ 1 }) || g == poly) {
        int deg = poly.get_degree() - 1;
        assert(deg > 0);
        auto genpol = get_random_polynomial(deg, modp);
        auto gpa = Polynomial::div(genpol, poly, modp);
        assert(gpa.first == Polynomial({}));
        auto gp = gpa.second;
        if (g == Polynomial({ 1 })) {
            Polynomial h;
            if (modp == 2) {
                assert(false);
            } else {
                int t = 1;
                for (int i = 0; i < degree - 1; i++) t *= modp;
                t /= 2;
                h = powmod(gp, t, poly, modp);
                h = Polynomial::sub(h, Polynomial({ 1 }), modp);
            }
            g = gcd(h, poly, modp);
        }
    }
    auto g2 = Polynomial::div(poly, g, modp).first;
    auto r1 = equal_degree_factorization(g, degree, modp);
    auto r2 = equal_degree_factorization(g2, degree, modp);

    result.insert(result.end(), r1.begin(), r1.end());
    result.insert(result.end(), r2.begin(), r2.end());

    return result;
}





vector<Polynomial> factor_square_free(Polynomial poly, int modp) {
    vector<Polynomial> result;

    auto distDeg = distinct_degree_factorization(poly, modp);

    for (auto t : distDeg) {
        auto r1 = equal_degree_factorization(t.first, t.second, modp);
        result.insert(result.end(), r1.begin(), r1.end());
    }

    return result;
}





std::vector<std::pair<Polynomial, int>> factor(Polynomial poly, int modp) {
    std::vector<std::pair<Polynomial, int>> result;

    std::vector<std::pair<Polynomial, int>> sqrfree = square_free_decomposition(poly, modp);
	
	for (auto const& value : sqrfree) {
        auto r1 = factor_square_free(value.first, modp);
        for (size_t i = 0; i < r1.size(); i++)
        {
            result.push_back({ r1[i], value.second });
        }
	}

	return result;
}
