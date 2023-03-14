#include "expressions/expressions.hpp"

#include "expressions/simplifier.hpp"

#include <stdexcept>

namespace cas::math {

    Addition::Addition(const Expression& left, const Expression& right)
        : BinaryExpression(left, right) {
    }

    Addition::Addition(Expression* left, Expression* right)
        : BinaryExpression(left, right) {
    }

    double Addition::getValue() const {
        return left->getValue() + right->getValue();
    }

    Expression* Addition::copy() const {
        return new Addition(left->copy(), right->copy());
    }

    ExpressionTypes Addition::getType() const {
        return ExpressionTypes::Addition;
    }

    Expression* Addition::simplify() const {
        return Simplifier::simplifyAddition(this);
    }

    Expression* Addition::differentiate(const Variable* var) const {
        return new Addition(left->differentiate(var), right->differentiate(var));
    }

    std::string Addition::toString() const {
        const std::string& rightString = right->toString();

        if (rightString.front() == '-') {
            return left->toString() + rightString;
        }
        else {
            return left->toString() + "+" + rightString;
        }
    }

} // namespace cas::math

#include <iostream>

std::ostream& operator<<(std::ostream& os, const cas::math::Addition& add) {
    return os << add.left << "+" << add.right;
}