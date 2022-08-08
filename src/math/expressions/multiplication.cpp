#include "math/expressions.hpp"

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

    ExpressionType Multiplication::getType() const {
        return ExpressionType::Multiplication;
    }

    Expression* Multiplication::simplify() const {
        return Simplifier::simplifyMultiplication(this);
    }

    std::string Multiplication::toString() const {
        std::string result;
        if (left->getType() < ExpressionType::Multiplication) {
            result += "(" + left->toString() + ")";
        }
        else {
            result += left->toString();
        }

        if (right->getType() == ExpressionType::Exponentiation) {
            Exponentiation* exp = reinterpret_cast<Exponentiation*>(right);

            if (exp->right->getType() == ExpressionType::Constant) {
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

        if (right->getType() < ExpressionType::Multiplication) {
            result += "(" + right->toString() + ")";
        }
        else {
            result += right->toString();
        }

        return result;
    }
} // namespace cas::math