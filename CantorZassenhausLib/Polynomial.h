#pragma once

#include <cstdlib>
#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>

class Polynomial
{
private:
    std::vector<int64_t> coeff;

public:
    Polynomial() {}

    Polynomial(std::vector<int64_t> coeff) : coeff(coeff) {};

    Polynomial(const Polynomial &polynomial) : coeff(polynomial.coeff) {};

    Polynomial &operator= (const Polynomial &polynomial) = default;

    int64_t get_degree() const;

    std::string to_string(std::string default_variable_name = "x") const;

    static Polynomial add(const Polynomial& a, const Polynomial& b, const int64_t modp = -1);

    static Polynomial sub(const Polynomial& a, const Polynomial& b, const int64_t modp = -1);

    static Polynomial mul(const Polynomial& a, const Polynomial& b, const int64_t modp = -1);

    static std::pair<Polynomial, Polynomial> div(const Polynomial& a, const Polynomial& b, const int64_t modp);

    friend bool operator== (const Polynomial &poly1, const Polynomial &poly2);
};


std::ostream & operator<<(std::ostream & Str, Polynomial const & v);

Polynomial parse_polynomial(std::string s);
