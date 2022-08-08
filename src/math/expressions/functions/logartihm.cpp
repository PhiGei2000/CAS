#include "math/expressions/functions/logarithm.hpp"

#include <cmath>

namespace cas::math {
    Ln::Ln(const Expression& argument)
        : argument(argument.copy()) {
    }

    Ln::Ln(Expression* argument)
        : argument(argument) {
    }

    std::string Ln::getName() const {
        return "ln";
    }

    double Ln::getValue() const {
        double argumentValue = argument->getValue();

        return log(argumentValue);
    }

    Expression* Ln::copy() const {
        return new Ln(argument->copy());
    }

    bool Ln::dependsOn(const Variable& var) const {
        return argument->dependsOn(var);
    }

    std::string Ln::toString() const {
        return getName() + "(" + argument->toString() + ")";
    }

    std::unordered_set<char> Ln::getVariables() const {
        return argument->getVariables();
    }
} // namespace cas::math