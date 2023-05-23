#include "expressions/functions/logarithm.hpp"

#include "expressions/operations.hpp"
#include <cmath>

namespace cas::math {
    // instantiateOperations(Ln)

    Ln::Ln(const Expression& argument)
        : Ln(argument.copy()) {
    }

    Ln::Ln(Expression* argument) {
        arguments[0] = assign(argument, this);
    }

    double Ln::getValue() const {
        double argumentValue = arguments[0]->getValue();

        return log(argumentValue);
    }

    Expression* Ln::copy() const {
        return new Ln(arguments[0]->copy());
    }

    Expression* Ln::simplify() const {
        Expression* argument = this->arguments[0]->simplify();

        if (NamedConstant* c = dynamic_cast<NamedConstant*>(argument)) {
            if (c->toString() == "e")
                return new Number(1);
        }

        return new Ln(argument);
    }

    Expression* Ln::getDerivative() const {
        return divide(1, arguments[0]);
    }
} // namespace cas::math