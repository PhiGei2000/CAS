#include "math/expressions/terms/differential.hpp"

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

    std::string Differential::toString() const {
        std::string result = "d";
        result += symbol;

        return result;
    }
} // namespace cas::math