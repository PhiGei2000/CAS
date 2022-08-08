#pragma once

#include <string>
#include <unordered_set>

namespace cas::math
{
enum class ExpressionType
{
    Addition,
    Multiplication,
    Exponentiation,
    Function,
    Constant,
    Variable,
    Differential
};

struct Variable;

struct Expression {
  public:
    virtual double getValue() const = 0;
    virtual Expression* copy() const = 0;
    virtual ExpressionType getType() const = 0;

    virtual bool dependsOn(const Variable& var) const = 0;

    virtual Expression* simplify() const;

    virtual std::string toString() const = 0;

    virtual std::unordered_set<char> getVariables() const = 0;
};
} // namespace cas::math