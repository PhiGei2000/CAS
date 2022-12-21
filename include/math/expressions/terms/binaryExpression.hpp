#pragma once

#include "expression.hpp"

namespace cas::math
{

struct BinaryExpression : public Expression {
  public:
    Expression* left = nullptr;
    Expression* right = nullptr;
    const bool commutative;

    BinaryExpression(const Expression& left, const Expression& right, bool commutative = true);
    BinaryExpression(Expression* left, Expression* right, bool commutative = true);
    ~BinaryExpression();

    virtual bool dependsOn(const Variable& var) const override;

    virtual void substitute(Expression* expression, Expression* newExpression) override;

    virtual std::set<Variable> getVariables() const override;
};

} // namespace cas::math