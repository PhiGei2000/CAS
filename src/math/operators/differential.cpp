#include "math/operators/differential.hpp"

#include <unordered_map>
#include <unordered_set>

namespace cas::math {
    Expression* D(Expression* expr) {
        std::unordered_set<char> variables = expr->getVariables();

        std::unordered_map<char, Expression*> derivatives;

        for (const auto& var : variables) {
            derivatives[var] = D(expr, Variable(var))->simplify();
        }

        if (derivatives.size() > 0) {
            auto it = derivatives.begin();

            Differential* d = new Differential((*it).first);
            Expression* result = new Multiplication((*it).second, d);
            it++;

            while (it != derivatives.end()) {
                Differential* d = new Differential((*it).first);
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

            case ExpressionType::Addition:
                addition = reinterpret_cast<Addition*>(expr);
                result = new Addition(D(addition->left, var), D(addition->right, var));
                break;
            case ExpressionType::Multiplication:
                multiplication = reinterpret_cast<Multiplication*>(expr);
                dLeft = D(multiplication->left, var);
                dRight = D(multiplication->right, var);

                result = new Addition(new Multiplication(dLeft, multiplication->right), new Multiplication(multiplication->left, dRight));
                break;
            case ExpressionType::Variable:
                variable = reinterpret_cast<Variable*>(expr);
                if (variable->getCharacter() == var.getCharacter()) {
                    result = new Constant(1);
                }
                else {
                    result = new Constant(0);
                }
                break;
            case ExpressionType::Exponentiation:
                exponentiation = reinterpret_cast<Exponentiation*>(expr);
                if (exponentiation->right->getType() == ExpressionType::Constant) {
                    double exponentValue = exponentiation->right->getValue();
                    if (exponentValue == 0) {
                        return new Constant(0);
                    }
                    else {
                        result = new Multiplication(new Constant(exponentValue), new Multiplication(new Exponentiation(exponentiation->left, new Constant(exponentValue - 1)), D(exponentiation->left, var)));
                    }
                }
                else {
                    // D(a^b) = a^b*(D(b)*ln a+b/a*D(a))

                    result = new Multiplication(exponentiation->copy(),
                                                new Addition(
                                                    new Multiplication(D(exponentiation->right, var), new Ln(exponentiation->left->copy())),
                                                    new Multiplication(
                                                        new Multiplication(exponentiation->right->copy(), new Exponentiation(exponentiation->left->copy(), new Constant(-1))),
                                                        D(exponentiation->left, var))));
                }
                break;
            case ExpressionType::Function:
                result = DFunction(reinterpret_cast<Function*>(expr), var);
                break;
            default:
                return nullptr;
        }

        return result;
    }

    Expression* DFunction(Function* function, const Variable& var) {
        const std::string& functionName = function->getName();

        if (functionName == "ln") {
            Ln* logarithm = reinterpret_cast<Ln*>(function);

            Expression* argument = logarithm->argument->copy();
            return new Multiplication(new Exponentiation(argument, new Constant(-1)), D(argument, var));
        }
        else if (functionName == "sin") {
            Sin* sin = reinterpret_cast<Sin*>(function);

            Expression* argument = sin->argument->copy();
            return new Multiplication(new Cos(argument), D(argument, var));
        }
        else if (functionName == "cos") {
            Cos* cos = reinterpret_cast<Cos*>(function);

            Expression* argument = cos->argument->copy();
            return new Multiplication(new Multiplication(new Constant(-1), new Sin(argument)), D(argument, var));
        }

        throw new std::runtime_error("Function derivative not implemated");
    }
} // namespace cas::math