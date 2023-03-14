#pragma once

#include <set>
#include <stdexcept>
#include <string>
#include <vector>

namespace cas::math {
    enum class ExpressionTypes {
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
        virtual ExpressionTypes getType() const = 0;
        virtual std::vector<Expression*> getChildren() const;

        virtual bool dependsOn(const Variable& var) const = 0;
        virtual constexpr bool isBinary() const {
            return false;
        }

        virtual Expression* simplify() const;
        virtual void substitute(Expression* expression, Expression* newExpression);

        virtual Expression* differentiate(const Variable* var) const = 0;

        virtual std::string toString() const = 0;

        virtual std::set<Variable> getVariables() const = 0;
    };

    Expression* assign(Expression* other, Expression* parent);
} // namespace cas::math