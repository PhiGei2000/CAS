#pragma once

#include "expression.hpp"

namespace cas::math {

    struct Constant : public Expression {
      protected:
        double value;

      public:
        Constant(double value);

        virtual double getValue() const override;
        virtual Expression* copy() const override;
        virtual ExpressionTypes getType() const override;

        virtual bool dependsOn(const Variable& var) const override;

        virtual Expression* differentiate(const Variable* var) const override;

        virtual std::string toString() const override;

        virtual std::set<Variable> getVariables() const override;
    };

    struct NamedConstant : public Constant {
      protected:
        std::string symbol;

      public:
        NamedConstant(const std::string& symbol, double value);

        virtual Expression* copy() const override;
        virtual ExpressionTypes getType() const override;

        virtual std::string toString() const override;
    };

    struct E : public NamedConstant {
      public:
        E();
    };

} // namespace cas::math
