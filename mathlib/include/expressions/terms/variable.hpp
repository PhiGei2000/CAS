#pragma once

#include "expressions/terms/expression.hpp"

#include <functional>

namespace cas::math {
    using VariableSymbol = char;

    struct Variable : public Expression {
      protected:
        VariableSymbol symbol;

      public:
        Variable(VariableSymbol character);

        VariableSymbol getSymbol() const;

        virtual bool dependsOn(const Variable& var) const override;

        virtual double getValue() const override;
        virtual Expression* copy() const override;
        virtual ExpressionTypes getType() const override;

        virtual Expression* differentiate(const Variable* var) const override;

        virtual std::string toString() const override;

        virtual std::set<Variable> getVariables() const override;

        bool operator==(const Variable& other) const;
    };

} // namespace cas::math

template<>
struct std::less<cas::math::Variable> {
    constexpr bool operator()(const cas::math::Variable& lhs, const cas::math::Variable& rhs) const;
};
