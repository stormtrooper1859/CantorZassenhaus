#include "Polynomial.h"

#include <string>
#include <algorithm>
#include <chrono>
#include <random>

#include "Utils.h"

using namespace std;

#include <iostream>

int64_t wtf = 0;


Polynomial::Polynomial(std::string str)
{
    try {
        auto monoms_string = split_by(str, "+");
        vector<pair<mpz_class, int>> monoms(monoms_string.size());

        for (size_t i = 0; i < monoms.size(); i++)
        {
            auto ss = split_by(monoms_string[i], "x");

            mpz_class coeff;
            int pwr;

            if (ss.size() == 1) {
                pwr = 0;
            } else {
                if (ss[1] == "") {
                    pwr = 1;
                } else {
                    pwr = stoi(ss[1].substr(1, ss[1].size()));
                }
            }

            if (ss[0] == "") {
                coeff = 1;
            } else {
                coeff = ss[0];
            }
            monoms[i] = { coeff, pwr };
        }


        int pwr = monoms[0].second;
        vector<mpz_class> result(pwr + 1);

        for (auto pr : monoms)
        {
            result[pr.second] = pr.first;
        }

        this->coeff = result;
    } catch (...) {
        cout << "Error during polynomial parse" << endl;
    }
}


void Polynomial::prune()
{
    for (int i = this->coeff.size(); i > 0 && this->coeff.back() == 0; i--)
    {
        this->coeff.pop_back();
    }
}


int Polynomial::get_degree() const
{
    return this->coeff.size() - 1;
}


std::string Polynomial::to_string(std::string default_variable_name) const
{
    int degree = this->coeff.size() - 1;
    std::string result = "";

    for (int i = degree; i >= 0; i--)
    {
        if (this->coeff[i] == 0) continue;
        if (!result.empty()) {
            result += "+";
        }

        if (this->coeff[i] != 1 || i == 0) {
            result += this->coeff[i].get_str();
        }
        if (i != 0) {
            result += default_variable_name;
            if (i != 1) {
                result += "^" + std::to_string(i);
            }
        }
    }

    if (result == "") {
        return "0";
    }

    return result;
}


Polynomial Polynomial::diff(const mpz_class modp)
{
    vector<mpz_class> v(this->get_degree());

    for (size_t i = 0; i < this->get_degree(); i++)
    {
        v[i] = (this->coeff[i + 1] * (i + 1)) % modp;
    }

    auto p = Polynomial(v);
    p.prune();

    return p;
}




Polynomial Polynomial::zip(const int n) const
{
    vector<mpz_class> v(this->get_degree() / n + 1);

    for (size_t i = 0; i <= this->get_degree(); i+=n)
    {
        v[i / n] = this->coeff[i];
    }

    return Polynomial(v);
}



std::ostream& operator<<(std::ostream& strm, const Polynomial& poly) {
    return strm << poly.to_string();
}







Polynomial Polynomial::add(const Polynomial & a, const Polynomial & b, const mpz_class modp)
{
    if (a == Polynomial({})) {
        return b;
    }
    if (b == Polynomial({})) {
        return a;
    }

    const Polynomial& a1 = a.get_degree() > b.get_degree() ? a : b;
    const Polynomial& b1 = a.get_degree() > b.get_degree() ? b : a;

    std::vector<mpz_class> v(a1.get_degree() + 1);

    for (size_t i = 0; i <= b1.get_degree(); i++)
    {
        v[i] = (a1.coeff[i] + b1.coeff[i] + modp) % modp;
    }

    for (size_t i = b1.get_degree() + 1; i <= a1.get_degree(); i++)
    {
        v[i] = a1.coeff[i];
    }

    Polynomial p = Polynomial(v);
    p.prune();
    return p;
}


//Polynomial Polynomial::mul(const Polynomial & a, const Polynomial & b, const mpz_class modp)
//{
//    if (a.is_zero() || b.is_zero()) {
//        return Polynomial({});
//    }
//
//    std::vector<mpz_class> v(a.get_degree() + b.get_degree() + 1);
//    
//    for (int i = 0; i <= a.get_degree(); ++i) {
//        for (int j = 0; j <= b.get_degree(); ++j) {
//            v[i + j] = (v[i + j] + a.coeff[i] * b.coeff[j]) % modp;
//        }
//    }
//
//    return Polynomial(v);
//}


const int len_f_naive = 42;


vector<mpz_class> naive_mul(const vector<mpz_class>& x, const vector<mpz_class>& y, mpz_class modp) {
    auto len = x.size();
    vector<mpz_class> res(2 * len);

    for (auto i = 0; i < len; ++i) {
        for (auto j = 0; j < len; ++j) {
            res[i + j] = (res[i + j] + x[i] * y[j]) % modp;
        }
    }

    return res;
}

vector<mpz_class> karatsuba_mul(const vector<mpz_class>& x, const vector<mpz_class>& y, mpz_class modp) {
    auto len = x.size();
    vector<mpz_class> res(2 * len);

    if (len <= len_f_naive) {
        return naive_mul(x, y, modp);
    }

    auto k = len / 2;

    vector<mpz_class> Xr{ x.begin(), x.begin() + k };
    vector<mpz_class> Xl{ x.begin() + k, x.end() };
    vector<mpz_class> Yr{ y.begin(), y.begin() + k };
    vector<mpz_class> Yl{ y.begin() + k, y.end() };

    vector<mpz_class> P1 = karatsuba_mul(Xl, Yl, modp);
    vector<mpz_class> P2 = karatsuba_mul(Xr, Yr, modp);

    vector<mpz_class> Xlr(k);
    vector<mpz_class> Ylr(k);

    for (int i = 0; i < k; ++i) {
        Xlr[i] = Xl[i] + Xr[i];
        Ylr[i] = Yl[i] + Yr[i];
    }

    vector<mpz_class> P3 = karatsuba_mul(Xlr, Ylr, modp);

    for (int i = 0; i < len; ++i) {
        P3[i] = (P3[i] - (P2[i] + P1[i]) + modp) % modp;
    }

    for (int i = 0; i < len; ++i) {
        res[i] = P2[i];
    }

    for (int i = len; i < 2 * len; ++i) {
        res[i] = P1[i - len];
    }

    for (int i = k; i < len + k; ++i) {
        res[i] = (res[i] + P3[i - k]) % modp;
        // TODO speed up by if
    }

    return res;
}


Polynomial Polynomial::mul(const Polynomial & a, const Polynomial & b, const mpz_class modp)
{
    vector<mpz_class> va = a.coeff;
    vector<mpz_class> vb = b.coeff;

    int mx = max(va.size(), vb.size());
    int rz = (mx & !(mx - 1)) == mx ? 0 : 1;
    while (mx > 0) {
        rz *= 2;
        mx /= 2;
    }

    for (int i = va.size(); i < rz; i++) {
        va.push_back(0);
    }
    for (int i = vb.size(); i < rz; i++) {
        vb.push_back(0);
    }
    
    auto vc = karatsuba_mul(va, vb, modp);
    Polynomial rez(vc);
    rez.prune();

    return rez;
}




Polynomial Polynomial::sub(const Polynomial & a, const Polynomial & b, const mpz_class modp)
{
    vector<mpz_class> v = b.coeff;

    for (int i = 0; i < v.size(); i++) {
        v[i] = modp - v[i];
    }

    return add(a, Polynomial(v), modp);
}


mpz_class inversed(mpz_class a, mpz_class modp) {
    mpz_class rezult;
    mpz_invert(rezult.get_mpz_t(), a.get_mpz_t(), modp.get_mpz_t());
    return rezult;
}





std::pair< Polynomial, Polynomial> Polynomial::div_internal(const Polynomial & a, const Polynomial & b, const mpz_class modp)
{
    mpz_class bl = b.coeff.back();
    Polynomial b2 = b.normalize(modp);

    int degree_of_result = a.get_degree() - b.get_degree() + 1;

    if (degree_of_result < 1) {
        return { Polynomial({}), a };
    }

    std::vector<mpz_class> coeff_result(degree_of_result);

    Polynomial at = a;

    for (int i = 0; i < degree_of_result; i++)
    {
        coeff_result[degree_of_result - 1 - i] = at.coeff[a.get_degree() - i];

        for (int j = 0; j <= b2.get_degree(); j++)
        {
            at.coeff[a.get_degree() - i - j] = (at.coeff[a.get_degree() - i - j] - coeff_result[degree_of_result - 1 - i] * b2.coeff[b2.get_degree() - j]) % modp;
            at.coeff[a.get_degree() - i - j] = (at.coeff[a.get_degree() - i - j] + modp) % modp;
        }
    }

    Polynomial quo = mul(Polynomial(coeff_result), Polynomial({ bl }), modp);
    
    at.prune();

    return { quo, at };
}


Polynomial Polynomial::div(const Polynomial & a, const Polynomial & b, const mpz_class modp)
{
    return Polynomial::div_internal(a, b, modp).first;
}


Polynomial Polynomial::mod(const Polynomial & a, const Polynomial & b, const mpz_class modp)
{
    return Polynomial::div_internal(a, b, modp).second;
}




Polynomial Polynomial::get_one()
{
    return Polynomial({ mpz_class(1) });
}

bool operator==(const Polynomial & poly1, const Polynomial & poly2)
{
    return poly1.coeff == poly2.coeff;
}

bool operator!=(const Polynomial & poly1, const Polynomial & poly2)
{
    return !(poly1 == poly2);
}


bool operator< (const Polynomial &poly1, const Polynomial &poly2) {
    if (poly1.coeff.size() == poly2.coeff.size()) {
        for (int i = poly1.coeff.size() - 1; i >= 0; i--) {
            if (poly1.coeff[i] != poly2.coeff[i]) {
                return poly1.coeff[i] < poly2.coeff[i];
            }
        }

        return false;
    }

    return poly1.coeff.size() < poly2.coeff.size();
}



Polynomial gcd(const Polynomial& a1, const Polynomial& b1, mpz_class modp)
{
    if (a1.is_zero()) {
        return b1;
    }
    if (b1.is_zero()) {
        return a1;
    }

    auto a = a1.normalize(modp);
    auto b = b1.normalize(modp);

    while (!b.is_zero()) {
        a = Polynomial::mod(a, b, modp);
        auto z = a;
        a = b;
        b = z;
    }

    return a.normalize(modp);
}

Polynomial powmod(const Polynomial& a, mpz_class b, const Polynomial& mod, mpz_class modp)
{
    mpz_class power = b;

    // Polynomial rez({ 1 });
    Polynomial rez = Polynomial::get_one();
    Polynomial aa = a;
    while (power > 0) {
        if (power % 2 == 1) {
            rez = Polynomial::mul(rez, aa, modp);
            rez = Polynomial::mod(rez, mod, modp);
        }
        aa = Polynomial::mul(aa, aa, modp);
        aa = Polynomial::mod(aa, mod, modp);
        power /= 2;
    }
    return rez;
}


Polynomial Polynomial::normalize(mpz_class modp) const
{
    mpz_class bl = this->coeff.back();
    mpz_class ib = inversed(bl, modp);

    vector<mpz_class> v = this->coeff;

    for (int i = 0; i < v.size(); i++) {
        v[i] = (v[i] * ib) % modp;
    }

    // return mul(*this, Polynomial({ ib }), modp);
    return Polynomial(v);
}

bool Polynomial::is_zero() const
{
    return *this == Polynomial({});
}

bool Polynomial::is_one() const
{
    return *this == Polynomial({ mpz_class(1) });
}

Polynomial::~Polynomial()
{
    wtf += 1;
}








Polynomial Polynomial::get_random_polynomial(int max_degree, mpz_class modq)
{
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    uniform_int_distribution<int> dist(0, modq.get_si() - 1);
    uniform_int_distribution<int> dist_degree(0, max_degree - 1);

    auto degree = dist_degree(rng) + 1;

    std::vector<mpz_class> vr(degree + 1);
    vr[degree] = 1;

    for (size_t i = 0; i < degree; i++)
    {
        vr[i] = dist(rng);
    }

    Polynomial result(vr);

    result.prune();

    return result;
}
