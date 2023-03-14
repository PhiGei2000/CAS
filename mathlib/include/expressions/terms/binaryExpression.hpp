#pragma once

#include "expression.hpp"

namespace cas::math {

    struct BinaryExpression : public Expression {
      public:
        Expression* left = nullptr;
        Expression* right = nullptr;
        const bool commutative;

        BinaryExpression(const Expression& left, const Expression& right, bool commutative = true);
        BinaryExpression(Expression* left, Expression* right, bool commutative = true);
        ~BinaryExpression();

        virtual std::vector<Expression*> getChildren() const override;

        virtual bool dependsOn(const Variable& var) const override;
        virtual constexpr bool isBinary() const override {
            return true;
        }

        virtual void replace(Expression* expression, Expression* newExpression) override;
        virtual void setVariable(Variable* var, Expression* expression) override;

        virtual std::set<Variable> getVariables() const override;
    };

} // namespace cas::math