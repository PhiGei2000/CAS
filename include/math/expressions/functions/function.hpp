#pragma once

#include "../terms/expression.hpp"

namespace cas::math {
    struct BaseFunction : public Expression {
        virtual std::string getName() const = 0;
        virtual Expression* getDerivative() const = 0;

        virtual ExpressionTypes getType() const {
            return ExpressionTypes::Function;
        }
    };

    template<int u>
    struct Function : public BaseFunction {
      public:
        Expression* arguments[u];

        virtual bool dependsOn(const Variable& var) const override;

        virtual std::string toString() const override;

        virtual std::set<Variable> getVariables() const override;

        virtual Expression* differentiate(const Variable* var) const override;
    };
} // namespace cas::math