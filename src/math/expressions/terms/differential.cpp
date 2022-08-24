#include "math/expressions/terms/differential.hpp"

namespace cas::math {
    Differential::Differential(VariableSymbol variable)
        : Variable(variable) {
    }

    Expression* Differential::copy() const {
        return new Differential(this->symbol);
    }

    ExpressionType Differential::getType() const {
        return ExpressionType::Differential;
    }

    std::string Differential::toString() const {
        std::string result = "d";
        result += symbol;

        return result;
    }
} // namespace cas::math