#pragma once

#include "expressions/addition.hpp"
#include "expressions/constant.hpp"
#include "expressions/exponentiation.hpp"
#include "expressions/multiplication.hpp"
#include "expressions/variable.hpp"
#include "expressions/differential.hpp"

#include "expressions/functions.hpp"

namespace cas::math {
    Addition operator+(const Expression& left, const Expression& right);
    Addition operator-(const Expression& left, const Expression& right);
    Multiplication operator*(const Expression& left, const Expression& right);
    Multiplication operator/(const Expression& left, const Expression& right);
} // namespace cas::math
