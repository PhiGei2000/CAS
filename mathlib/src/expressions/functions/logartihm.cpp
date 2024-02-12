#include "expressions/functions/logarithm.hpp"

#include "expressions/operations.hpp"
#include "expressions/terms/numeric/constants.hpp"
#include <cmath>

namespace cas::math {
    // instantiateOperations(Ln)

    Ln::Ln(const Expression& argument)
        : Ln(argument.copy()) {
    }

    Ln::Ln(Expression* argument)
        : Function<1>("ln") {
        arguments[0] = assign(argument, this);
    }

    Number Ln::getValue() const {
        Number argumentValue = arguments[0]->getValue();
        return log(argumentValue.realValue);
    }

    Expression* Ln::copy() const {
        return new Ln(arguments[0]->copy());
    }

    Expression* Ln::getDerivative() const {
        return divide(1, arguments[0]);
    }
} // namespace cas::math