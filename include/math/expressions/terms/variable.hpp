#pragma once

#include "math/expressions/terms/expression.hpp"

#include <functional>

template<>
struct std::hash<cas::math::Variable> {
    std::size_t operator()(const cas::math::Variable& var) const noexcept;
};

namespace cas::math {
    typedef char VariableSymbol;

    struct Variable : public Expression {
      protected:
        VariableSymbol symbol;

      public:
        Variable(VariableSymbol character);

        VariableSymbol getSymbol() const;

        virtual bool dependsOn(const Variable& var) const override;

        virtual double getValue() const override;
        virtual Expression* copy() const override;
        virtual ExpressionType getType() const override;

        virtual std::string toString() const override;

        virtual std::unordered_set<Variable> getVariables() const override;

        bool operator==(const Variable& other) const;
    };
} // namespace cas::math

