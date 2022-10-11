#pragma once

#include "binaryExpression.hpp"

namespace cas::math {
    struct Exponentiation : public BinaryExpression {
      public:
        Exponentiation(const Expression& left, const Expression& right);
        Exponentiation(Expression* base, Expression* exponent);

        virtual double getValue() const override;
        virtual Expression* copy() const override;
        virtual ExpressionTypes getType() const override;

        virtual Expression* simplify() const override;

        virtual std::string toString() const override;
    };

} // namespace cas::math
