#pragma once

#include "expressions/terms/expression.hpp"

#include <functional>

namespace cas::math {
    using VariableSymbol = std::string;

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
    inline constexpr bool operator()(const cas::math::Variable& lhs, const cas::math::Variable& rhs) const {
        const cas::math::VariableSymbol lhsSymbol = lhs.getSymbol();
        const cas::math::VariableSymbol rhsSymbol = rhs.getSymbol();

        // compare size of the strings if they dont have the same lenght
        if (lhsSymbol.size() != rhsSymbol.size()) {
            return lhsSymbol.size() < rhsSymbol.size();
        }

        // compare the first characters that are different
        size_t pos = 0;
        size_t maxPos = lhsSymbol.size(); // the size of the strings is equal
        while (lhsSymbol[pos] == rhsSymbol[pos]) {
            if (pos >= maxPos)
                return false;

            pos++;
        }

        return lhsSymbol[pos] < rhsSymbol[pos];
    }
};
