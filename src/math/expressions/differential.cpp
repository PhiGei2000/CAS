#include "math/expressions/differential.hpp"

namespace cas::math {
    Differential::Differential(char variable)
        : Variable(variable) {
    }

    ExpressionType Differential::getType() const {
        return ExpressionType::Differential;
    }

    std::string Differential::toString() const {
        std::string result = "d";
        result += character;

        return result;
    }
} // namespace cas::math