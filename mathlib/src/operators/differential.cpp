#include "operators/differential.hpp"

#include <map>
#include <set>

namespace cas::math {
    Expression* D(Expression* expr) {
        std::set<Variable> variables = expr->getVariables();

        std::map<Variable, Expression*> derivatives;

        for (const auto& var : variables) {
            derivatives[var] = D(expr, Variable(var))->simplify();
        }

        if (derivatives.size() > 0) {
            auto it = derivatives.begin();

            Differential* d = new Differential((*it).first.getSymbol());
            Expression* result = new Multiplication((*it).second, d);
            it++;

            while (it != derivatives.end()) {
                Differential* d = new Differential((*it).first.getSymbol());
                Expression* prod = new Multiplication((*it).second, d);

                Expression* sum = new Addition(prod, result);
                result = sum;
                it++;
            }

            return result;
        }

        return new Number(0);
    }

    Expression* D(Expression* expr, const Variable& var) {
        if (!expr->dependsOn(var)) {
            return new Number(0);
        }

        Expression* result = nullptr;
        Addition* addition;
        Multiplication* multiplication;
        Exponentiation* exponentiation;
        const Variable* variable;
        Expression* dLeft;
        Expression* dRight;
        switch (expr->getType()) {
            case ExpressionTypes::Addition:
                addition = reinterpret_cast<Addition*>(expr);
                result = new Addition(D(addition->left, var), D(addition->right, var));
                break;
            case ExpressionTypes::Multiplication:
                multiplication = reinterpret_cast<Multiplication*>(expr);
                dLeft = D(multiplication->left, var);
                dRight = D(multiplication->right, var);

                result = new Addition(new Multiplication(dLeft, multiplication->right->copy()), new Multiplication(multiplication->left->copy(), dRight));
                break;
            case ExpressionTypes::Variable:
                variable = reinterpret_cast<Variable*>(expr);
                if (variable->getSymbol() == var.getSymbol()) {
                    result = new Number(1);
                }
                else {
                    result = new Number(0);
                }
                break;
            case ExpressionTypes::Exponentiation:
                exponentiation = reinterpret_cast<Exponentiation*>(expr);
                if (exponentiation->right->getType() == ExpressionTypes::Constant) {
                    double exponentValue = exponentiation->right->getValue();
                    if (exponentValue == 0) {
                        return new Number(0);
                    }
                    else {
                        result = new Multiplication(new Number(exponentValue), new Multiplication(new Exponentiation(exponentiation->left->copy(), new Number(exponentValue - 1)), D(exponentiation->left, var)));
                    }
                }
                else {
                    // base transform (a^b = e^(ln(a)*b))
                    Expression* baseLn = new Ln(exponentiation->left->copy());
                    Expression* eExponent = new Multiplication(baseLn, exponentiation->right->copy());

                    result = new Multiplication(exponentiation->copy(), D(eExponent, var));

                    // delete eExponent and baseLn (baseLn is left of eExponent and gets deleted if the destructor of eExponent is called)
                    delete eExponent;
                }
                break;
            case ExpressionTypes::Function:
                result = reinterpret_cast<BaseFunction*>(expr)->differentiate(&var);
                break;
            default:
                return nullptr;
        }

        return result;
    }
} // namespace cas::math