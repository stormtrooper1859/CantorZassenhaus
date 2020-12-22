#include "Polynomial.h"

#include <string>
#include <algorithm>

#include "Utils.h"

using namespace std;







Polynomial::Polynomial(std::string str)
{
    auto monoms_string = split_by(str, "+");
    vector<pair<mpz_class, int>> monoms(monoms_string.size());

    for (size_t i = 0; i < monoms.size(); i++)
    {
        auto ss = split_by(monoms_string[i], "x^");
        monoms[i] = { mpz_class(ss[0]), stoi(ss[1]) };
    }

    int pwr = monoms[0].second;
    vector<mpz_class> result(pwr + 1);

    for (auto pr : monoms) {
        result[pr.second] = pr.first;
    }

    this->coeff = result;
}

Polynomial parse_polynomial(std::string str)
{
    return Polynomial(str);
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
            // result += std::to_string(this->coeff[i]);
            result += this->coeff[i].get_str();
        }
        if (i != 0) {
            result += default_variable_name;
            if (i != 1) {
                result += "^" + std::to_string(i);
            }
        }
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
        v[i] = a.coeff[i];
    }

    Polynomial p = Polynomial(v);
    p.prune();
    return p;
}


Polynomial Polynomial::mul(const Polynomial & a, const Polynomial & b, const mpz_class modp)
{
    if (a == Polynomial({}) || b == Polynomial({})) {
        return Polynomial({});
    }


    std::vector<mpz_class> v(a.get_degree() + b.get_degree() + 1);
    
    for (int i = 0; i <= a.get_degree(); ++i) {
        for (int j = 0; j <= b.get_degree(); ++j) {
            if (modp == -1) {
                v[i + j] = (v[i + j] + a.coeff[i] * b.coeff[j]);
            }
            else {
                v[i + j] = (v[i + j] + a.coeff[i] * b.coeff[j]) % modp;
                v[i + j] = (v[i + j] + modp) % modp;
            }
        }
    }
    Polynomial p = Polynomial();
    p.coeff = v;
    return p;
}


Polynomial Polynomial::sub(const Polynomial & a, const Polynomial & b, const mpz_class modp)
{
    return add(a, mul(b, Polynomial({ mpz_class(-1) }), modp), modp);
}


mpz_class bin_pow(mpz_class a, mpz_class power, mpz_class modp) {
    mpz_class rez = 1;
    while (power > 0) {
        if (power % 2 == 1) {
            rez = (rez * a) % modp;
        }
        a = (a * a) % modp;
        power /= 2;
    }
    return rez;
}

mpz_class inversed(mpz_class a, mpz_class modp) {
    return bin_pow(a, modp - 2, modp);
}





std::pair< Polynomial, Polynomial> Polynomial::div(const Polynomial & a, const Polynomial & b, const mpz_class modp)
{
    mpz_class bl = b.coeff.back();
    //mpz_class ib = inversed(bl, modp);
    //Polynomial b2 = mul(b, Polynomial({ ib }), modp);

     Polynomial b2 = b.normalize(modp);

    int degree_of_result = a.get_degree() - b.get_degree() + 1;

    if (degree_of_result < 1) {
        return { Polynomial({}), a };
    }

    std::vector<mpz_class> coeff_result(degree_of_result);

    Polynomial at = a;

    int c1 = coeff_result.size();
    int c2 = at.coeff.size();
    int c3 = b2.coeff.size();
    int c4 = b2.get_degree();

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
    Polynomial rem(at.coeff);
    rem.prune();

    return { quo, rem };
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




Polynomial gcd(Polynomial a1, Polynomial b1, mpz_class modp)
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
        a = Polynomial::div(a, b, modp).second;
        auto z = a;
        a = b;
        b = z;
    }

    return a.normalize(modp);
}

Polynomial powmod(Polynomial a, int b, Polynomial mod, mpz_class modp)
{
    int power = b;

    // Polynomial rez({ 1 });
    Polynomial rez = Polynomial::get_one();
    Polynomial aa = a;
    while (power > 0) {
        if (power % 2) {
            rez = Polynomial::mul(rez, aa, modp);
            rez = Polynomial::div(rez, mod, modp).second;
        }
        aa = Polynomial::mul(aa, aa, modp);
        aa = Polynomial::div(aa, mod, modp).second;
        power /= 2;
    }
    return rez;
}


Polynomial Polynomial::normalize(mpz_class modp) const
{
    mpz_class bl = this->coeff.back();
    mpz_class ib = inversed(bl, modp);

    return mul(*this, Polynomial({ ib }), modp);
}

bool Polynomial::is_zero() const
{
    return *this == Polynomial({});
}

bool Polynomial::is_one() const
{
    return *this == Polynomial({ mpz_class(1) });
}








