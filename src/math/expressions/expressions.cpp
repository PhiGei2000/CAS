#include "math/expressions/expressions.hpp"

namespace cas::math
{
Addition operator+(const Expression& left, const Expression& right) {
    return Addition(left, right);
}

Addition operator-(const Expression& left, const Expression& right) {
    return Addition(left, Multiplication(Constant(-1), right));
}

Multiplication operator*(const Expression& left, const Expression& right) {
    return Multiplication(left, right);
}

Multiplication operator/(const Expression& left, const Expression& right) {
    return Multiplication(left, Exponentiation(right, Constant(-1)));
}

} // namespace cas::math
