#include "expressions/terms/differential.hpp"

#include "except.hpp"

namespace cas::math {
    Differential::Differential(VariableSymbol variable)
        : Variable(variable) {
    }

    Expression* Differential::copy() const {
        return new Differential(this->symbol);
    }

    ExpressionTypes Differential::getType() const {
        return ExpressionTypes::Differential;
    }

    Expression* Differential::differentiate(const Variable* var) const {
        // we will need some exterior algebra here
        throw std::not_implemented_error("The exterior product is needed to derterminate the derivative of a differential");
    }

    std::string Differential::toString() const {
        std::string result = "d";
        result += symbol;

        return result;
    }
} // namespace cas::math