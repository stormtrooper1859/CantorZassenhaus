#include "Polynomial.h"

#include <string>
#include <algorithm>

#include "Utils.h"

using namespace std;













std::vector<int64_t> prune(std::vector<int64_t>& v) {
    std::vector<int64_t> vr;

    int i = 0;
    for (i = 0; i < v.size() && v[i] == 0; i++);
    for (; i < v.size(); i++) {
        vr.push_back(v[i]);
    }

    return vr;
}


Polynomial parse_polynomial(std::string str)
{
    auto monoms_string = split_by(str, "+");
    vector<pair<int, int>> monoms(monoms_string.size());

    for (size_t i = 0; i < monoms.size(); i++)
    {
        auto ss = split_by(monoms_string[i], "x^");
        monoms[i] = { stoi(ss[0]), stoi(ss[1]) };
    }

    int pwr = monoms[0].second;
    vector<int64_t> result(monoms[0].second + 1);

    for (auto pr : monoms) {
        result[pwr - pr.second] = pr.first;
    }

    return Polynomial(result);
}


int64_t Polynomial::get_degree() const
{
    return this->coeff.size() - 1;
}



std::string Polynomial::to_string(std::string default_variable_name) const
{
    int degree = this->coeff.size() - 1;
    std::string result = "";

    for (size_t i = 0; i <= degree; i++)
    {
        if (this->coeff[i] == 0) continue;
        if (!result.empty()) {
            result += "+";
        }

        if (this->coeff[i] != 1 || degree - i == 0) {
            result += std::to_string(this->coeff[i]);
        }
        if (degree - i != 0) {
            result += default_variable_name;
            if (degree - i != 1) {
                result += "^" + std::to_string(degree - i);
            }
        }
    }

    return result;
}



std::ostream& operator<<(std::ostream& strm, const Polynomial& poly) {
    return strm << poly.to_string();
}





Polynomial Polynomial::add(const Polynomial & a, const Polynomial & b, const int64_t modp)
{
    std::vector<int64_t> v(std::max(a.coeff.size(), b.coeff.size()));

    const Polynomial& a1 = a.get_degree() > b.get_degree() ? a : b;
    const Polynomial& b1 = a.get_degree() > b.get_degree() ? b : a;

    std::copy(a1.coeff.begin(), a1.coeff.end(), v.begin());

    size_t diff = a1.get_degree() - b1.get_degree();

    for (int i = b1.get_degree(); i >= 0; i--)
    {
        if (modp == -1) {
            v[diff + i] = (v[diff + i] + b1.coeff[i]);
        }
        else {
            v[diff + i] = (v[diff + i] + b1.coeff[i]) % modp;
        }
    }

    //std::vector<int64_t> vr;

    //int i = 0;
    //for (i = 0; i < v.size() && v[i] == 0; i++);
    //for (; i < v.size(); i++) {
        //vr.push_back(v[i]);
    //}

    Polynomial p = Polynomial();
    //p.coeff = vr;
    p.coeff = prune(v);
    return p;
}


Polynomial Polynomial::mul(const Polynomial & a, const Polynomial & b, const int64_t modp)
{
    std::vector<int64_t> v(a.get_degree() + b.get_degree() + 1);
    for (int i = 0; i <= a.get_degree(); ++i) {
        for (int j = 0; j <= b.get_degree(); ++j) {
            if (modp == -1) {
                v[i + j] = (v[i + j] + a.coeff[i] * b.coeff[j]);
            }
            else {
                v[i + j] = (v[i + j] + a.coeff[i] * b.coeff[j]) % modp;
            }
        }
    }
    Polynomial p = Polynomial();
    p.coeff = v;
    return p;
}


Polynomial Polynomial::sub(const Polynomial & a, const Polynomial & b, const int64_t modp)
{
    return add(a, mul(b, Polynomial({ -1 })), modp);
}


int64_t bin_pow(int64_t a, int64_t power, int64_t modp) {
    int rez = 1;
    while (power > 0) {
        if (power % 2) {
            rez = (rez * a) % modp;
        }
        a = (a * a) % modp;
        power /= 2;
    }
    return rez;
}

int64_t inversed(int64_t a, int64_t modp) {
    return bin_pow(a, modp - 2, modp);
}





std::pair< Polynomial, Polynomial> Polynomial::div(const Polynomial & a, const Polynomial & b, const int64_t modp)
{
    int64_t bl = b.coeff[0];
    int64_t ib = inversed(bl, modp);

    Polynomial b2 = mul(b, Polynomial({ ib }));

    int degree_of_result = a.get_degree() - b.get_degree() + 1;
    std::vector<int64_t> coeff_result(degree_of_result);

    Polynomial at = a;

    int c1 = coeff_result.size();
    int c2 = at.coeff.size();
    int c3 = b2.coeff.size();
    int c4 = b2.get_degree();

    for (int i = 0; i < degree_of_result; i++)
    {
        coeff_result[i] = at.coeff[i];
        for (int j = 0; j <= b2.get_degree(); j++)
        {
            at.coeff[i + j] = (at.coeff[i + j] - coeff_result[i] * b2.coeff[j]) % modp;
            at.coeff[i + j] = (at.coeff[i + j] + modp) % modp;
        }
    }

    Polynomial quo = mul(Polynomial(coeff_result), Polynomial({ bl }), modp);
    Polynomial rem(prune(at.coeff));

    return { quo, rem };
}

bool operator==(const Polynomial & poly1, const Polynomial & poly2)
{
    return poly1.coeff == poly2.coeff;
}
