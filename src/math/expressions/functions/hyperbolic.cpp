#include "math/expressions/functions/hyperbolic.hpp"

#include "math/expressions/terms/multiplication.hpp"

#include <cmath>

namespace cas::math {
#pragma region Sinh
    Sinh::Sinh(const Expression& argument) {
        arguments[0] = assign(argument.copy(), this);
    }

    Sinh::Sinh(Expression* argument) {
        arguments[0] = assign(argument, this);
    }

    std::string Sinh::getName() const {
        return "sinh";
    }

    double Sinh::getValue() const {
        double argValue = arguments[0]->getValue();
        return sinh(argValue);
    }

    Expression* Sinh::copy() const {
        return new Sinh(arguments[0]);
    }

    Expression* Sinh::getDerivative() const {
        return new Cosh(arguments[0]);
    }
#pragma endregion

#pragma region Cosh
    Cosh::Cosh(const Expression& argument) {
        arguments[0] = assign(argument.copy(), this);
    }

    Cosh::Cosh(Expression* argument) {
        arguments[0] = assign(argument, this);
    }

    std::string Cosh::getName() const {
        return "cosh";
    }

    double Cosh::getValue() const {
        double argValue = arguments[0]->getValue();
        return cosh(argValue);
    }

    Expression* Cosh::copy() const {
        return new Cosh(arguments[0]);
    }

    Expression* Cosh::getDerivative() const {
        return new Sinh(arguments[0]);
    }
} // namespace cas::math
