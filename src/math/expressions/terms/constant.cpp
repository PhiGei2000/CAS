#include "math/expressions/terms/constant.hpp"

#include "math/expressions/terms/variable.hpp"

#if WIN32
#include <numbers>
#endif
#include <cmath>


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

    std::unordered_set<Variable> Constant::getVariables() const {
        return {};
    }

#pragma region NamedConstants
    NamedConstant::NamedConstant(const std::string& symbol, double value)
        : symbol(symbol), Constant(value) {
    }

    Expression* NamedConstant::copy() const {
        return new NamedConstant(symbol, value);
    }

    ExpressionType NamedConstant::getType() const {
        return ExpressionType::NamedConstant;
    }

    std::string NamedConstant::toString() const {
        return symbol;
    }

    E::E()        
        : NamedConstant("e", std::numbers::e) {        
    }

#pragma endregion
} // namespace cas::math