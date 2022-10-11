#include "math/expressions/expressions.hpp"

#include "math/expressions/simplifier.hpp"

#include <math.h>
#include <sstream>

namespace cas::math {
    Exponentiation::Exponentiation(const Expression& left, const Expression& right)
        : BinaryExpression(left, right, false) {
    }

    Exponentiation::Exponentiation(Expression* base, Expression* exponent)
        : BinaryExpression(base, exponent, false) {
    }

    double Exponentiation::getValue() const {
        return pow(left->getValue(), right->getValue());
    }

    Expression* Exponentiation::copy() const {
        return new Exponentiation(left->copy(), right->copy());
    }

    ExpressionTypes Exponentiation::getType() const {
        return ExpressionTypes::Exponentiation;
    }

    Expression* Exponentiation::simplify() const {
        return Simplifier::simplifyExponentiation(this);
    }

    std::string Exponentiation::toString() const {
        std::stringstream ss;
        bool bracketsLeft = left->getType() <= ExpressionTypes::Exponentiation;

        if (bracketsLeft)
            ss << "(";

        ss << left->toString();

        if (bracketsLeft)
            ss << ")";

        ss << "^";

        bool bracketsRight = right->getType() < ExpressionTypes::Exponentiation;
        if (bracketsRight)
            ss << "(";

        ss << right->toString();
        if (bracketsRight)
            ss << ")";

        return ss.str();
    }
} // namespace cas::math

#include <ostream>

std::ostream& operator<<(std::ostream& os, const cas::math::Exponentiation& exp) {
    return os << exp.toString();
}
