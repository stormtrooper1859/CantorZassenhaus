#pragma once

#include <cstdlib>
#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>

class Polynomial
{
public:
    std::vector<int64_t> coeff;

    Polynomial() {}

    Polynomial(std::vector<int64_t> coeff) : coeff(coeff) {};

    Polynomial(const Polynomial &polynomial) : coeff(polynomial.coeff) {};

    Polynomial &operator= (const Polynomial &polynomial) = default;

    int64_t get_degree() const;

    std::string to_string(std::string default_variable_name = "x") const;
};


int degPoly(const Polynomial& a);


std::ostream & operator<<(std::ostream & Str, Polynomial const & v);



Polynomial add(const Polynomial& a, const Polynomial& b, const int64_t modp = -1);

Polynomial sub(const Polynomial& a, const Polynomial& b, const int64_t modp = -1);

Polynomial mul(const Polynomial& a, const Polynomial& b, const int64_t modp = -1);

std::pair<Polynomial, Polynomial> div(const Polynomial& a, const Polynomial& b, const int64_t modp);

bool operator== (const Polynomial &poly1, const Polynomial &poly2);
