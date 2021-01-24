#pragma once

#include <vector>

#include "mpirxx.h"

#include "Polynomial.h"

std::vector<std::pair<Polynomial, int>> factor(const Polynomial& poly, const mpz_class& modp);

