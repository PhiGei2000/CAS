#include "math/operators/differential.hpp"

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

        return new Constant(0);
    }

    Expression* D(Expression* expr, const Variable& var) {
        if (!expr->dependsOn(var)) {
            return new Constant(0);
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
                    result = new Constant(1);
                }
                else {
                    result = new Constant(0);
                }
                break;
            case ExpressionTypes::Exponentiation:
                exponentiation = reinterpret_cast<Exponentiation*>(expr);
                if (exponentiation->right->getType() == ExpressionTypes::Constant) {
                    double exponentValue = exponentiation->right->getValue();
                    if (exponentValue == 0) {
                        return new Constant(0);
                    }
                    else {
                        result = new Multiplication(new Constant(exponentValue), new Multiplication(new Exponentiation(exponentiation->left->copy(), new Constant(exponentValue - 1)), D(exponentiation->left, var)));
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
                result = DFunction(reinterpret_cast<BaseFunction*>(expr), var);
                break;
            default:
                return nullptr;
        }

        return result;
    }

    Expression* DFunction(BaseFunction* function, const Variable& var) {
        const std::string& functionName = function->getName();

        if (functionName == "ln") {
            Ln* logarithm = reinterpret_cast<Ln*>(function);

            Expression* argument = logarithm->argument->copy();
            return new Multiplication(new Exponentiation(argument, new Constant(-1)), D(argument, var));
        }
        else if (functionName == "sin") {
            Sin* sin = reinterpret_cast<Sin*>(function);

            Expression* argument = sin->arguments[0]->copy();
            return new Multiplication(new Cos(argument), D(argument, var));
        }
        else if (functionName == "cos") {
            Cos* cos = reinterpret_cast<Cos*>(function);

            Expression* argument = cos->arguments[0]->copy();
            return new Multiplication(new Multiplication(new Constant(-1), new Sin(argument)), D(argument, var));
        }

        throw new std::runtime_error("Function derivative not implemented");
    }
} // namespace cas::math