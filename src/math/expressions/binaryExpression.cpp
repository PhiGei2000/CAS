#include "math/expressions/binaryExpression.hpp"

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

} // namespace cas::math