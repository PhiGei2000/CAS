#pragma once

#include "expressions/terms/binaryExpression.hpp"

namespace cas::math {

    struct Multiplication : public BinaryExpression {
      public:
        Multiplication(const Expression& left, const Expression& right);
        Multiplication(Expression* left, Expression* right);

        virtual double getValue() const override;
        virtual Expression* copy() const override;
        virtual ExpressionTypes getType() const override;

        virtual Expression* simplify() const override;

        virtual Expression* differentiate(const Variable* var) const override;

        virtual std::string toString() const override;
    };

} // namespace cas::math