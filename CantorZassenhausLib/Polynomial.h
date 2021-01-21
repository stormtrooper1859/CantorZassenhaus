#pragma once

#include <cstdlib>
#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>

#include "mpirxx.h"

extern int64_t wtf;

//[DebuggerDisplay("{DebuggerDisplay,nq}")]
class Polynomial
{
public:
//private:
    std::vector <mpz_class> coeff;

    void prune();

    Polynomial(std::vector<mpz_class> coeff) : coeff(coeff) {};

    static std::pair<Polynomial, Polynomial> div_internal(const Polynomial& a, const Polynomial& b, const mpz_class modp);

public:
    Polynomial() {}

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

    static Polynomial div(const Polynomial& a, const Polynomial& b, const mpz_class modp);

    static Polynomial mod(const Polynomial& a, const Polynomial& b, const mpz_class modp);

    static Polynomial get_one();

    static Polynomial get_random_polynomial(int max_degree, mpz_class modq);

    Polynomial normalize(mpz_class modp) const;

    bool is_zero() const;

    bool is_one() const;

    friend bool operator== (const Polynomial &poly1, const Polynomial &poly2);
    friend bool operator!= (const Polynomial &poly1, const Polynomial &poly2);

    ~Polynomial();
};


std::ostream & operator<<(std::ostream & Str, Polynomial const & v);

Polynomial parse_polynomial(std::string s);


Polynomial gcd(const Polynomial& a, const Polynomial& b, mpz_class modp);

Polynomial powmod(const Polynomial& a, mpz_class b, const Polynomial& mod, mpz_class modp);
