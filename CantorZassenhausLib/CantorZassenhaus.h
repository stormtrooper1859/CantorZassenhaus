#pragma once


#include <vector>
#include "Polynomial.h"

std::vector<std::pair<Polynomial, int>> factor(Polynomial poly, int modp);

Polynomial get_random_polynomial(int max_degree, int modq);
