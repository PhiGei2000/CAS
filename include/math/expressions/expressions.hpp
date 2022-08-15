#pragma once

#include "addition.hpp"
#include "constant.hpp"
#include "exponentiation.hpp"
#include "multiplication.hpp"
#include "variable.hpp"
#include "differential.hpp"
#include "functions.hpp"

namespace cas::math {
    Addition operator+(const Expression& left, const Expression& right);
    Addition operator-(const Expression& left, const Expression& right);
    Multiplication operator*(const Expression& left, const Expression& right);
    Multiplication operator/(const Expression& left, const Expression& right);
} // namespace cas::math
