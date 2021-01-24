#include "CantorZassenhaus.h"

#include <algorithm>
#include <chrono>
#include <iostream>


using namespace std;


std::vector<std::pair<Polynomial, int>> square_free_decomposition(Polynomial poly, mpz_class modp) {
    std::vector<std::pair<Polynomial, int>> result;

    Polynomial a = poly;
    Polynomial c;
    int m = 1;

    do {
        auto ad = a.diff(modp);
        c = gcd(a, ad, modp);
        auto w = Polynomial::div(a, c, modp);
        int i = 1;
        while (!w.is_one()) {
            auto y = gcd(w, c, modp);
            auto qq = Polynomial::div(w, y, modp);
            if (!qq.is_one()) {
                result.push_back({ qq, i * m });
            }
            w = y;
            c = Polynomial::div(c, y, modp);
            i++;
        }
        if (!c.is_one()) {
            a = c.zip(modp.get_si());
            m = m * modp.get_si();
        }
    } while (!c.is_one());

	return result;
}



vector<pair<Polynomial, int>> distinct_degree_factorization(Polynomial poly, mpz_class modp) {
    vector<pair<Polynomial, int>> result;

    Polynomial h("1x^1");
    Polynomial href = h;
    auto f = poly;
    int i = 1;

    while (!f.is_one()) {
        h = powmod(h, modp, poly, modp);
        auto sbs = Polynomial::sub(h, href, modp);
        auto g = gcd(sbs, f, modp);
        if (!g.is_one()) {
            result.push_back({ g, i });
            f = Polynomial::div(f, g, modp);
        }
        i++;
    }

    return result;
}



vector<Polynomial> equal_degree_factorization(Polynomial poly, int degree, mpz_class modp) {
    if (poly.get_degree() == degree) {
        return vector<Polynomial>({ poly });
    }

	vector<Polynomial> result;

    Polynomial g = Polynomial::get_one();
    Polynomial genpol;

    while (g.is_one() || g == poly) {
        int deg = poly.get_degree() - 1;
        genpol = Polynomial::get_random_polynomial(deg, modp);
        auto gp = Polynomial::mod(genpol, poly, modp);
        g = gcd(gp, poly, modp);
        if (g.is_one()) {
            Polynomial h;
            if (modp == 2) {
                for (size_t j = 0; j < degree; j++)
                {
                    mpz_class t;
                    mpz_pow_ui(t.get_mpz_t(), mpz_class(2).get_mpz_t(), j);

                    auto t2 = powmod(gp, t, poly, modp);
                    h = Polynomial::mod(Polynomial::add(h, t2, modp), poly, modp);
                }
            } else {
                mpz_class t;
                mpz_pow_ui(t.get_mpz_t(), modp.get_mpz_t(), degree);
                t /= 2;

                h = powmod(gp, t, poly, modp);
                h = Polynomial::sub(h, Polynomial::get_one(), modp);
            }
            g = gcd(h, poly, modp);
        }
    }
    auto g2 = Polynomial::div(poly, g, modp);
    auto r1 = equal_degree_factorization(g, degree, modp);
    auto r2 = equal_degree_factorization(g2, degree, modp);

    result.insert(result.end(), r1.begin(), r1.end());
    result.insert(result.end(), r2.begin(), r2.end());

    return result;
}


vector<Polynomial> factor_square_free(Polynomial poly, mpz_class modp) {
    vector<Polynomial> result;

    auto distDeg = distinct_degree_factorization(poly, modp);

    for (auto t : distDeg) {
        auto r1 = equal_degree_factorization(t.first, t.second, modp);
        result.insert(result.end(), r1.begin(), r1.end());
    }

    return result;
}


std::vector<std::pair<Polynomial, int>> factor(Polynomial poly, mpz_class modp) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::vector<std::pair<Polynomial, int>> result;

    std::vector<std::pair<Polynomial, int>> sqrfree = square_free_decomposition(poly, modp);
	
	for (auto const& value : sqrfree) {
        auto r1 = factor_square_free(value.first, modp);
        for (size_t i = 0; i < r1.size(); i++)
        {
            result.push_back({ r1[i], value.second });
        }
	}

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Computation time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

	return result;
}
