#pragma once


#include <vector>
#include "Polynomial.h"

std::vector<std::pair<Polynomial, int>> factor(Polynomial poly, int modp);

Polynomial get_random_polynomial(int max_degree, int modq);


std::vector<std::pair<Polynomial, int>> square_free_decomposition(Polynomial poly, int modp);

std::vector<std::pair<Polynomial, int>> distinct_degree_factorization(Polynomial poly, int modp);

std::vector<Polynomial> equal_degree_factorization(Polynomial poly, int degree, int modp);
