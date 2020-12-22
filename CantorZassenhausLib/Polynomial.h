#pragma once

#include <cstdlib>
#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>

class Polynomial
{
public:
//private:
    std::vector<int64_t> coeff;

    void prune();

//public:
    Polynomial() {}

    Polynomial(std::vector<int64_t> coeff) : coeff(coeff) {};

    Polynomial(const Polynomial &polynomial) : coeff(polynomial.coeff) {};

    Polynomial &operator= (const Polynomial &polynomial) = default;

    int64_t get_degree() const;

    std::string to_string(std::string default_variable_name = "x") const;

    Polynomial diff(const int64_t modp);

    Polynomial zip(const int64_t n) const;

    static Polynomial add(const Polynomial& a, const Polynomial& b, const int64_t modp = -1);

    static Polynomial sub(const Polynomial& a, const Polynomial& b, const int64_t modp = -1);

    static Polynomial mul(const Polynomial& a, const Polynomial& b, const int64_t modp = -1);

    static std::pair<Polynomial, Polynomial> div(const Polynomial& a, const Polynomial& b, const int64_t modp);

    Polynomial normalize(int modp) const;

    friend bool operator== (const Polynomial &poly1, const Polynomial &poly2);
    friend bool operator!= (const Polynomial &poly1, const Polynomial &poly2);
};


std::ostream & operator<<(std::ostream & Str, Polynomial const & v);

Polynomial parse_polynomial(std::string s);



Polynomial gcd(Polynomial a, Polynomial b, int modp);

Polynomial powmod(Polynomial a, int b, Polynomial mod, int modp);