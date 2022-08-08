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
    virtual ExpressionType getType() const override;

    virtual bool dependsOn(const Variable& var) const override;

    virtual std::string toString() const override;

    virtual std::unordered_set<char> getVariables() const override;
};

}
