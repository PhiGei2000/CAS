#include "math/expressions/terms/binaryExpression.hpp"

#include <iostream>

namespace cas::math
{

BinaryExpression::BinaryExpression(const Expression& left, const Expression& right) {
    this->left = left.copy();
    this->right = right.copy();
}

BinaryExpression::BinaryExpression(Expression* left, Expression* right) :
left(left), right(right){

}

BinaryExpression::~BinaryExpression() {
    delete left;
    delete right;
}

bool BinaryExpression::dependsOn(const Variable& var) const {
    return left->dependsOn(var) || right->dependsOn(var);
}

std::unordered_set<char> BinaryExpression::getVariables() const {
    std::unordered_set<char> leftVars = left->getVariables();
    std::unordered_set<char> rightVars = right->getVariables();

    std::unordered_set<char> vars = leftVars;
    vars.merge(rightVars);

    return vars;
}

} // namespace cas::math