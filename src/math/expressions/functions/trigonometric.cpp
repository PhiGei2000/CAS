#include "math/expressions/functions/trigonometric.hpp"

#include "math/expressions/terms/constant.hpp"
#include "math/expressions/terms/exponentiation.hpp"
#include "math/expressions/terms/multiplication.hpp"
#include "math/expressions/terms/variable.hpp"

#include <cmath>

namespace cas::math {

#pragma region Sin
    Sin::Sin(const Expression& argument) {
        arguments[0] = assign(argument.copy(), this);
    }

    Sin::Sin(Expression* argument) {
        arguments[0] = assign(argument, this);
    }

    std::string Sin::getName() const {
        return "sin";
    }

    double Sin::getValue() const {
        double argValue = arguments[0]->getValue();

        return sin(argValue);
    }

    Expression* Sin::copy() const {
        return new Sin(arguments[0]->copy());
    }

    Expression* Sin::differentiate(const Variable* var) const {
        Expression* dArg = arguments[0]->differentiate(var);

        return new Multiplication(new Cos(arguments[0]), dArg);
    }
#pragma endregion

#pragma region Cos
    Cos::Cos(const Expression& argument) {
        arguments[0] = assign(argument.copy(), this);
    }

    Cos::Cos(Expression* argument) {
        arguments[0] = assign(argument, this);
    }

    std::string Cos::getName() const {
        return "cos";
    }

    double Cos::getValue() const {
        double argValue = arguments[0]->getValue();

        return cos(argValue);
    }

    Expression* Cos::copy() const {
        return new Cos(arguments[0]->copy());
    }

    Expression* Cos::differentiate(const Variable* var) const {
        Expression* dArg = arguments[0]->differentiate(var);

        return new Multiplication(new Constant(-1), new Multiplication(new Sin(arguments[0]), dArg));
    }

#pragma endregion

#pragma region Tan
    Tan::Tan(const Expression& argument) {
        arguments[0] = assign(argument.copy(), this);
    }

    Tan::Tan(Expression* argument) {
        arguments[0] = assign(argument, this);
    }

    std::string Tan::getName() const {
        return "tan";
    }

    double Tan::getValue() const {
        double argValue = arguments[0]->getValue();

        return tan(argValue);
    }

    Expression* Tan::copy() const {
        return new Tan(arguments[0]->copy());
    }

    Expression* Tan::differentiate(const Variable* var) const {
        Expression* dArg = arguments[0]->differentiate(var);

        return new Multiplication(dArg, new Exponentiation(new Cos(arguments[0]), new Constant(-2)));
    }
#pragma endregion
} // namespace cas::math
