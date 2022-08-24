#pragma once

#include <stdexcept>
#include <string>
#include <unordered_set>

namespace cas::math {
    enum class ExpressionType {
        Addition,
        Multiplication,
        Exponentiation,
        Function,
        Constant,
        NamedConstant,
        Variable,
        Differential
    };

    struct Variable;

    struct no_value_error : public std::runtime_error {
        no_value_error(const std::string& message);
    };

    struct Expression {
      public:
        Expression* parent = nullptr;

        virtual ~Expression();

        virtual double getValue() const = 0;
        virtual Expression* copy() const = 0;
        virtual ExpressionType getType() const = 0;

        virtual bool dependsOn(const Variable& var) const = 0;

        virtual Expression* simplify() const;
        virtual void substitute(Expression* expression, Expression* newExpression);

        virtual std::string toString() const = 0;

        virtual std::unordered_set<Variable> getVariables() const = 0;
    };
} // namespace cas::math