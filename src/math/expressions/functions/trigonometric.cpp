#include "math/expressions/functions/trigonometric.hpp"

#include "math/expressions/terms/variable.hpp"

#include <cmath>

namespace cas::math {

#pragma region Sin
    Sin::Sin(const Expression& argument)
        : argument(argument.copy()) {
    }

    Sin::Sin(Expression* argument)
        : argument(argument) {
    }

    std::string Sin::getName() const {
        return "sin";
    }

    double Sin::getValue() const {
        double argValue = argument->getValue();

        return sin(argValue);
    }

    Expression* Sin::copy() const {
        return new Sin(argument->copy());
    }

    bool Sin::dependsOn(const Variable& var) const {
        return argument->dependsOn(var);
    }

    std::string Sin::toString() const {
        return getName() + "(" + argument->toString() + ")";
    }

    std::unordered_set<Variable> Sin::getVariables() const {
        return argument->getVariables();
    }
#pragma endregion

#pragma region Cos
    Cos::Cos(const Expression& argument)
        : argument(argument.copy()) {
    }

    Cos::Cos(Expression* argument)
        : argument(argument) {
    }

    std::string Cos::getName() const {
        return "cos";
    }

    double Cos::getValue() const {
        double argValue = argument->getValue();

        return cos(argValue);
    }

    Expression* Cos::copy() const {
        return new Cos(argument->copy());
    }

    bool Cos::dependsOn(const Variable& var) const {
        return argument->dependsOn(var);
    }

    std::string Cos::toString() const {
        return getName() + "(" + argument->toString() + ")";
    }

    std::unordered_set<Variable> Cos::getVariables() const {
        return argument->getVariables();
    }
#pragma endregion
} // namespace cas::math
