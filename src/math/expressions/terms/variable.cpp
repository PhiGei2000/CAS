#include "math/expressions/terms/variable.hpp"

#include <stdexcept>

namespace cas::math {

    Variable::Variable(char character)
        : character(character) {
    }

    char Variable::getCharacter() const {
        return character;
    }

    bool Variable::dependsOn(const Variable& var) const {
        return character == var.character;
    }

    double Variable::getValue() const {
        throw std::runtime_error("Cannot get value of a variable");
    }

    Expression* Variable::copy() const {
        return new Variable(*this);
    }

    ExpressionType Variable::getType() const {
        return ExpressionType::Variable;
    }

    std::string Variable::toString() const {
        return std::string(1, character);
    }

    std::unordered_set<char> Variable::getVariables() const {
        return {character};
    }

} // namespace cas::math