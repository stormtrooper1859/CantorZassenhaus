#pragma once

#include <cstdlib>
#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>

#include "mpirxx.h"

class Polynomial
{
public:
private:
    std::vector <mpz_class> coeff;

    void prune();

    Polynomial() {}

    Polynomial(std::vector<mpz_class> coeff) : coeff(coeff) {};

public:
    Polynomial(std::string s);

    Polynomial(const Polynomial &polynomial) : coeff(polynomial.coeff) {};

    Polynomial &operator= (const Polynomial &polynomial) = default;

    int get_degree() const;

    std::string to_string(std::string default_variable_name = "x") const;

    Polynomial diff(const mpz_class modp);

    Polynomial zip(const int n) const;

    static Polynomial add(const Polynomial& a, const Polynomial& b, const mpz_class modp);

    static Polynomial sub(const Polynomial& a, const Polynomial& b, const mpz_class modp);

    static Polynomial mul(const Polynomial& a, const Polynomial& b, const mpz_class modp);

    static std::pair<Polynomial, Polynomial> div(const Polynomial& a, const Polynomial& b, const mpz_class modp);

    static Polynomial get_one();

    Polynomial normalize(mpz_class modp) const;

    bool is_zero() const;

    bool is_one() const;

    friend bool operator== (const Polynomial &poly1, const Polynomial &poly2);
    friend bool operator!= (const Polynomial &poly1, const Polynomial &poly2);
};


std::ostream & operator<<(std::ostream & Str, Polynomial const & v);

Polynomial parse_polynomial(std::string s);



Polynomial gcd(Polynomial a, Polynomial b, mpz_class modp);

Polynomial powmod(Polynomial a, int b, Polynomial mod, mpz_class modp);
