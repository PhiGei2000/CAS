#include "math/expressions/terms/binaryExpression.hpp"

#include "math/expressions/terms/variable.hpp"

#include <iostream>

namespace cas::math {

    BinaryExpression::BinaryExpression(const Expression& left, const Expression& right, bool commutative)
        : left(left.copy()), right(right.copy()), commutative(commutative) {
    }

    BinaryExpression::BinaryExpression(Expression* left, Expression* right, bool commutative)
        : left(left), right(right), commutative(commutative) {
    }

    BinaryExpression::~BinaryExpression() {
        delete left;
        delete right;
    }

    bool BinaryExpression::dependsOn(const Variable& var) const {
        return left->dependsOn(var) || right->dependsOn(var);
    }

    std::unordered_set<Variable> BinaryExpression::getVariables() const {
        std::unordered_set<Variable> leftVars = left->getVariables();
        std::unordered_set<Variable> rightVars = right->getVariables();

        std::unordered_set<Variable> vars = leftVars;
        vars.merge(rightVars);

        return vars;
    }

} // namespace cas::math