#pragma once

#include "terms/addition.hpp"
#include "terms/constant.hpp"
#include "terms/exponentiation.hpp"
#include "terms/multiplication.hpp"
#include "terms/variable.hpp"
#include "terms/differential.hpp"
#include "functions.hpp"

namespace cas::math {
    Addition operator+(const Expression& left, const Expression& right);
    Addition operator-(const Expression& left, const Expression& right);
    Multiplication operator*(const Expression& left, const Expression& right);
    Multiplication operator/(const Expression& left, const Expression& right);
} // namespace cas::math
