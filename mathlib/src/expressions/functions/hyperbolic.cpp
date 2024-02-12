#include "expressions/functions/hyperbolic.hpp"

#include "expressions/operations.hpp"

#include <cmath>

namespace cas::math {
#pragma region Sinh
    Sinh::Sinh(const Expression& argument)
        : Function<1>("sinh") {
        arguments[0] = assign(argument.copy(), this);
    }

    Sinh::Sinh(Expression* argument)
        : Function<1>("sinh") {
        arguments[0] = assign(argument, this);
    }

    Number Sinh::getValue() const {
        Number argValue = arguments[0]->getValue();
        return sinh(argValue.realValue);
    }

    Expression* Sinh::copy() const {
        return new Sinh(arguments[0]);
    }

    Expression* Sinh::simplify() const {
        if (arguments[0]->getType() == ExpressionTypes::Function) {
            Function* argument = reinterpret_cast<Function*>(arguments[0]);
            if (argument->name == "asinh") {
                return argument->arguments[0];
            }
        }

        return copy();
    }

    Expression* Sinh::getDerivative() const {
        return new Cosh(arguments[0]);
    }
#pragma endregion

#pragma region Asinh
    Asinh::Asinh(const Expression& argument)
        : Function<1>("asinh") {
        arguments[0] = assign(argument.copy(), this);
    }

    Asinh::Asinh(Expression* argument)
        : Function<1>("asinh") {
        arguments[0] = assign(argument, this);
    }

    Number Asinh::getValue() const {
        Number argValue = arguments[0]->getValue();
        return asinh(argValue.realValue);
    }

    Expression* Asinh::copy() const {
        return new Asinh(arguments[0]);
    }

    Expression* Asinh::simplify() const {
        if (arguments[0]->getType() == ExpressionTypes::Function) {
            Function* function = reinterpret_cast<Function*>(arguments[0]);
            if (function->name == "sinh") {
                return function->arguments[0];
            }
        }

        return this->copy();
    }

    Expression* Asinh::getDerivative() const {
        return divide(1, sqrt(add(arguments[0], 2)));
    }
#pragma endregion

#pragma region Cosh
    Cosh::Cosh(const Expression& argument)
        : Function<1>("cosh") {
        arguments[0] = assign(argument.copy(), this);
    }

    Cosh::Cosh(Expression* argument)
        : Function<1>("cosh") {
        arguments[0] = assign(argument, this);
    }

    Number Cosh::getValue() const {
        Number argValue = arguments[0]->getValue();
        return cosh(argValue.realValue);
    }

    Expression* Cosh::copy() const {
        return new Cosh(arguments[0]);
    }

    Expression* Cosh::simplify() const {
        if (arguments[0]->getType() == ExpressionTypes::Function) {
            Function* function = reinterpret_cast<Function*>(arguments[0]);
            if (function->name == "acosh") {
                return function->arguments[0];
            }
        }

        return this->copy();
    }

    Expression* Cosh::getDerivative() const {
        return new Sinh(arguments[0]);
    }
#pragma endregion

#pragma region Acosh
    Acosh::Acosh(const Expression& argument)
        : Acosh(argument.copy()) {
    }

    Acosh::Acosh(Expression* argument)
        : Function<1>("acosh") {
        arguments[0] = assign(argument, this);
    }

    Number Acosh::getValue() const {
        Number argValue = arguments[0]->getValue();
        return acosh(argValue.realValue);
    }

    Expression* Acosh::copy() const {
        return new Acosh(arguments[0]);
    }

    Expression* Acosh::simplify() const {
        if (arguments[0]->getType() == ExpressionTypes::Function) {
            Function* function = reinterpret_cast<Function*>(arguments[0]);
            if (function->name == "cosh") {
                return function->arguments[0];
            }
        }

        return this->copy();
    }

    Expression* Acosh::getDerivative() const {
        return divide(1, sqrt(subtract(power(arguments[0], 2), 1)));
    }
#pragma endregion

} // namespace cas::math
