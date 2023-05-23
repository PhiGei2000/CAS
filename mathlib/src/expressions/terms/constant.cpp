#include "expressions/terms/constant.hpp"

#include "expressions/terms/variable.hpp"

#if WIN32
#include <numbers>
#endif
#include <cmath>


namespace cas::math {
    Number::Number(double value)
        : value(value) {
    }

    double Number::getValue() const {
        return value;
    }

    Expression* Number::copy() const {
        return new Number(value);
    }

    ExpressionTypes Number::getType() const {
        return ExpressionTypes::Constant;
    }

    bool Number::dependsOn(const Variable& var) const {
        return false;
    }

    Expression* Number::differentiate(const Variable* var) const {
        return new Number(0);
    }

    std::string Number::toString() const {
        std::string str = std::to_string(value);

        // remove leading zeros
        if (str.find('.') != std::string::npos) {
            while (str.back() == '0') {
                str.pop_back();
            }
        }
        if (str.back() == '.') {
            str.pop_back();
        }

        return str;
    }

    std::set<Variable> Number::getVariables() const {
        return {};
    }
} // namespace cas::math