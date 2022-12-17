#include "math/expressions/expressions.hpp"

#include "math/expressions/simplifier.hpp"

namespace cas::math {
    Multiplication::Multiplication(const Expression& left, const Expression& right)
        : BinaryExpression(left, right) {
    }

    Multiplication::Multiplication(Expression* left, Expression* right)
        : BinaryExpression(left, right) {
    }

    double Multiplication::getValue() const {
        return left->getValue() * right->getValue();
    }

    Expression* Multiplication::copy() const {
        return new Multiplication(left->copy(), right->copy());
    }

    ExpressionTypes Multiplication::getType() const {
        return ExpressionTypes::Multiplication;
    }

    Expression* Multiplication::simplify() const {
        return Simplifier::simplifyMultiplication(this);
    }

    Expression* Multiplication::differentiate(const Variable* var) const {
        // calculate the derivative of the two factors
        Expression* dLeft = left->differentiate(var);
        Expression* dRight = right->differentiate(var);

        // apply product rule
        Expression* rLeft = new Multiplication(dLeft, right);
        Expression* rRight = new Multiplication(left, dRight);

        Expression* result = new Addition(rLeft, rRight);

        return result;
    }

    std::string Multiplication::toString() const {
        std::string result;
        if (left->getType() < ExpressionTypes::Multiplication) {
            result += "(" + left->toString() + ")";
        }
        else {
            result += left->toString();
        }

        if (right->getType() == ExpressionTypes::Exponentiation) {
            Exponentiation* exp = reinterpret_cast<Exponentiation*>(right);

            if (exp->right->getType() == ExpressionTypes::Constant) {
                double value = exp->right->getValue();

                if (value < 0) {
                    result += "/";

                    result += "(" + exp->left->toString() + ")";
                    if (value != -1) {
                        result += "^" + exp->right->toString();
                    }

                    return result;
                }
            }
        }

        result += "*";

        if (right->getType() < ExpressionTypes::Multiplication) {
            result += "(" + right->toString() + ")";
        }
        else {
            result += right->toString();
        }

        return result;
    }
} // namespace cas::math