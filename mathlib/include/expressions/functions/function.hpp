#pragma once

#include "../terms/expression.hpp"
#include "../terms/multiplication.hpp"
#include "../terms/variable.hpp"

#include <sstream>

namespace cas::math {
    struct BaseFunction : public Expression {
        const std::string name;
        virtual Expression* getDerivative() const = 0;

        virtual ExpressionTypes getType() const {
            return ExpressionTypes::Function;
        }
    };

    template<int u>
    struct Function : public BaseFunction {
      public:
        Expression* arguments[u];

        virtual std::vector<Expression*> getChildren() const override {
            return std::vector<Expression*>(std::begin(arguments), std::end(arguments));
        }

        virtual bool dependsOn(const Variable& var) const override {
            for (const Expression* arg : arguments) {
                if (arg->dependsOn(var)) {
                    return true;
                }
            }

            return false;
        }

        virtual std::string toString() const override {
            std::stringstream result;
            result << name << "(" << arguments[0]->toString();

            for (int i = 1; i < u; i++) {
                result << ", " << arguments[i]->toString();
            }

            result << ")";
            return result.str();
        }

        virtual std::set<Variable> getVariables() const override {
            std::set<Variable> vars = arguments[0]->getVariables();
            for (int i = 1; i < u; i++) {
                vars.merge(arguments[i]->getVariables());
            }

            return vars;
        }

        virtual Expression* differentiate(const Variable* var) const override {
            Expression* result = getDerivative();

            for (int i = 0; i < u; i++) {
                Expression* dArg = arguments[i]->differentiate(var);
                Multiplication* prod = new Multiplication(result, dArg);
                result = prod;
            }

            return result;
        }
    };
} // namespace cas::math