#include "math/expressions/functions/logarithm.hpp"

#include "math/expressions/operations.hpp"
#include <cmath>

namespace cas::math {
    // instantiateOperations(Ln)

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

    Expression* Ln::simplify() const {
        Expression* argument = this->argument->simplify();

        if (NamedConstant* c = dynamic_cast<NamedConstant*>(argument)) {
            if (c->toString() == "e")
                return new Constant(1);
        }

        return new Ln(argument);
    }

    Expression* Ln::getDerivative() const {
        return divide(1, arguments[0]);
    }
} // namespace cas::math