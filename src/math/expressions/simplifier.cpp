#include "math/expressions/simplifier.hpp"

namespace cas::math {
    Expression* Simplifier::simplify(const Expression* expr) {
        ExpressionType type = expr->getType();

        switch (type) {
            case ExpressionType::Addition:
                return simplifyAddition(reinterpret_cast<const Addition*>(expr));
            case ExpressionType::Multiplication:
                return simplifyMultiplication(reinterpret_cast<const Multiplication*>(expr));
            default:
                return expr->copy();
        }
    }

    Expression* Simplifier::simplifyAddition(const Addition* sum) {
        // simplify both summands
        Expression* left = sum->left->simplify();
        Expression* right = sum->right->simplify();

        // evaluate numerical values if the summands are constants
        if (left->getType() == ExpressionType::Constant) {
            double leftValue = left->getValue();
            if (right->getType() == ExpressionType::Constant) {
                double value = leftValue + right->getValue();

                return new Constant(value);
            }
            // ignore first summand if it is zero
            else if (leftValue == 0) {
                return right;
            }
        }

        // ignore second summand if it is zero
        if (right->getType() == ExpressionType::Constant) {
            double rightValue = right->getValue();
            if (rightValue == 0)
                return left;
        }

        return new Addition(left, right);
    }

    Expression* Simplifier::simplifyMultiplication(const Multiplication* prod) {
        // simplyfy both factors
        Expression* left = prod->left->simplify();
        Expression* right = prod->right->simplify();

        // evaluate numerical values if the factors are constants
        if (left->getType() == ExpressionType::Constant) {
            double leftValue = left->getValue();
            if (right->getType() == ExpressionType::Constant) {
                double value = leftValue * right->getValue();
                return new Constant(value);
            }
            // ignore fist factor if it is one
            else if (leftValue == 1) {
                return right;
            }
            // if one factor is zero then the product is zero
            else if (leftValue == 0) {
                return new Constant(0);
            }
        }

        if (right->getType() == ExpressionType::Constant) {
            double rightValue = right->getValue();

            // ignore second factor if it is one
            if (rightValue == 1) {
                return left;
            }
            // if one factor is zero then the product is zero
            else if (rightValue == 0) {
                return new Constant(0);
            }
        }

        return new Multiplication(left, right);
    }
} // namespace cas::math