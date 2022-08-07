#include "math/expressions/constant.hpp"

namespace cas::math {
    Constant::Constant(double value)
        : value(value) {
    }

    double Constant::getValue() const {
        return value;
    }

    Expression* Constant::copy() const {
        return new Constant(value);
    }

    ExpressionType Constant::getType() const {
        return ExpressionType::Constant;
    }

    bool Constant::dependsOn(const Variable& var) const {
        return false;
    }

    std::string Constant::toString() const {
        std::string str = std::to_string(value);

        // remove leading zeros
        while(str.back() == '0') {
            str.pop_back();
        }

        if (str.back() == '.') {
            str.pop_back();
        }

        return str;
    }

} // namespace cas::math