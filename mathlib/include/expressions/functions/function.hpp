#pragma once

#include "../terms/expression.hpp"
#include "../terms/multiplication.hpp"
#include "../terms/variable.hpp"

#include <sstream>

namespace cas::math {
    struct BaseFunction : public Expression {
        const std::string name;
        virtual Expression* getDerivative() const = 0;

        inline virtual ExpressionTypes getType() const {
            return ExpressionTypes::Function;
        }
    };

    template<int u>
    struct Function : public BaseFunction {
      public:
        Expression* arguments[u];

        inline virtual std::vector<Expression*> getChildren() const override {
            return std::vector<Expression*>(std::begin(arguments), std::end(arguments));
        }

        inline virtual bool dependsOn(const Variable& var) const override {
            for (const Expression* arg : arguments) {
                if (arg->dependsOn(var)) {
                    return true;
                }
            }

            return false;
        }

        inline virtual void replace(Expression* expr, Expression* newExpr) override {
            for (int i = 0; i < u; i++) {
                if (arguments[i] == expr) {
                    delete arguments[i];
                    arguments[i] = newExpr->copy();
                }
                else {
                    arguments[i]->replace(expr, newExpr);
                }
            }
        }

        inline virtual void setVariable(Variable* var, Expression* expr) override {
            for (int i = 0; i < u; i++) {
                if (arguments[i]->getType() == ExpressionTypes::Variable) {
                    Variable* argVar = static_cast<Variable*>(arguments[i]);
                    if (*argVar == *var) {
                        delete argVar;

                        arguments[i] = expr->copy();
                        arguments[i]->parent = this;
                    }
                }
                else {
                    arguments[i]->setVariable(var, expr);
                }
            }
        }

        inline virtual std::string toString() const override {
            std::stringstream result;
            result << name << "(" << arguments[0]->toString();

            for (int i = 1; i < u; i++) {
                result << ", " << arguments[i]->toString();
            }

            result << ")";
            return result.str();
        }

        inline virtual std::set<Variable> getVariables() const override {
            std::set<Variable> vars = arguments[0]->getVariables();
            for (int i = 1; i < u; i++) {
                vars.merge(arguments[i]->getVariables());
            }

            return vars;
        }

        inline virtual Expression* differentiate(const Variable* var) const override {
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