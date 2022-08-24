#pragma once

#include "expression.hpp"

namespace cas::math
{

struct BinaryExpression : public Expression {
  public:
    Expression* left = nullptr;
    Expression* right = nullptr;

    BinaryExpression(const Expression& left, const Expression& right);
    BinaryExpression(Expression* left, Expression* right);
    ~BinaryExpression();

    virtual bool dependsOn(const Variable& var) const override;

    virtual std::unordered_set<char> getVariables() const override;
};

} // namespace cas::math