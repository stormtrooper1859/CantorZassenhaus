#pragma once


#include <vector>
#include "Polynomial.h"

std::vector<std::pair<Polynomial, int>> factor(Polynomial poly, int modp);

