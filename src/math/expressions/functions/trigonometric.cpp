#include "math/expressions/functions/trigonometric.hpp"

#include "math/expressions/operations.hpp"

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
        return new Sin(arguments[0]);
    }

    Expression* Sin::getDerivative() const {
        return new Cos(arguments[0]);
    }
#pragma endregion

#pragma region Arcsin
    Arcsin::Arcsin(const Expression& argument) {
        arguments[0] = assign(argument.copy(), this);
    }

    Arcsin::Arcsin(Expression* argument) {
        arguments[0] = assign(argument, this);
    }

    std::string Arcsin::getName() const {
        return "arcsin";
    }

    double Arcsin::getValue() const {
        double argValue = arguments[0]->getValue();

        return asin(argValue);
    }

    Expression* Arcsin::copy() const {
        return new Arcsin(arguments[0]);
    }

    Expression* Arcsin::getDerivative() const {
        return divide(1, sqrt(subtract(1, power(arguments[0], 2))));
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
        return new Cos(arguments[0]);
    }

    Expression* Cos::getDerivative() const {
        return multiply(-1, new Sin(arguments[0]));
    }
#pragma endregion

#pragma region Arccos
    Arccos::Arccos(const Expression& argument) {
        arguments[0] = assign(argument.copy(), this);
    }

    Arccos::Arccos(Expression* argument) {
        arguments[0] = assign(argument, this);
    }

    std::string Arccos::getName() const {
        return "arccos";
    }

    double Arccos::getValue() const {
        double argValue = arguments[0]->getValue();

        return acos(argValue);
    }

    Expression* Arccos::copy() const {
        return new Arccos(arguments[0]);
    }

    Expression* Arccos::getDerivative() const {
        return divide(-1, sqrt(subtract(1, power(arguments[0], 2))));
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
        return new Tan(arguments[0]);
    }

    Expression* Tan::getDerivative() const {
        return add(1, power(new Tan(arguments[0]->copy()), 2));
    }

#pragma endregion

#pragma region Arctan
    Arctan::Arctan(const Expression& argument)
        : Arctan(argument.copy()) {
    }

    Arctan::Arctan(Expression* argument) {
        arguments[0] = assign(argument, this);
    }

    std::string Arctan::getName() const {
        return "arctan";
    }

    double Arctan::getValue() const {
        double argValue = arguments[0]->getValue();

        return atan(argValue);
    }

    Expression* Arctan::copy() const {
        return new Arctan(arguments[0]);
    }

    Expression* Arctan::getDerivative() const {
        return divide(1, add(1, power(arguments[0], 2)));
    }
#pragma endregion
} // namespace cas::math
