#pragma once


#include <vector>
#include "Polynomial.h"

#include "mpirxx.h"

std::vector<std::pair<Polynomial, int>> factor(Polynomial poly, mpz_class modp);

// Polynomial get_random_polynomial(int max_degree, mpz_class modq);


std::vector<std::pair<Polynomial, int>> square_free_decomposition(Polynomial poly, mpz_class modp);

std::vector<std::pair<Polynomial, int>> distinct_degree_factorization(Polynomial poly, mpz_class modp);

std::vector<Polynomial> equal_degree_factorization(Polynomial poly, int degree, mpz_class modp);
