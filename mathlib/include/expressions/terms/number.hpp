#pragma once

#include "expression.hpp"

namespace cas::math {

    struct Number : public Expression {      
      public:
        double realValue;

        Number(double realValue);

        virtual Number getValue() const override;
        virtual Expression* copy() const override;
        virtual ExpressionTypes getType() const override;

        virtual bool dependsOn(const Variable& var) const override;

        virtual Expression* differentiate(const Variable* var) const override;

        virtual std::string toString() const override;

        virtual std::set<Variable> getVariables() const override;

        virtual bool operator==(const Number& other) const;
    };

} // namespace cas::math
