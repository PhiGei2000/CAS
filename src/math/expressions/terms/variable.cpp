#include "math/expressions/terms/variable.hpp"

#include <stdexcept>

std::size_t std::hash<cas::math::Variable>::operator()(const cas::math::Variable& var) const noexcept {
    return std::hash<cas::math::VariableSymbol>{}(var.getSymbol());
}

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

    ExpressionType Variable::getType() const {
        return ExpressionType::Variable;
    }

    std::string Variable::toString() const {
        return std::string(1, symbol);
    }

    std::unordered_set<Variable> Variable::getVariables() const {
        return {Variable(symbol)};
    }

    bool Variable::operator==(const Variable& other) const {
        return symbol == other.symbol;
    }

} // namespace cas::math