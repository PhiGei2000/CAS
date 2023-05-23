#include "expressions/terms/variable.hpp"

#include "expressions/terms/constant.hpp"

#include <stdexcept>

namespace cas::math {

    Variable::Variable(VariableSymbol character)
        : symbol(character) {
    }

    VariableSymbol Variable::getSymbol() const {
        return symbol;
    }

    bool Variable::dependsOn(const Variable& var) const {
        return symbol == var.symbol;
    }

    double Variable::getValue() const {
        throw no_value_error("Cannot get value of a variable");
    }

    Expression* Variable::copy() const {
        return new Variable(*this);
    }

    ExpressionTypes Variable::getType() const {
        return ExpressionTypes::Variable;
    }

    Expression* Variable::differentiate(const Variable* var) const {
        if (*this == *var) {
            return new Number(1);
        }

        return new Number(0);
    }

    std::string Variable::toString() const {
        return symbol;
    }

    std::set<Variable> Variable::getVariables() const {
        return {Variable(symbol)};
    }

    bool Variable::operator==(const Variable& other) const {
        return symbol == other.symbol;
    }

} // namespace cas::math
