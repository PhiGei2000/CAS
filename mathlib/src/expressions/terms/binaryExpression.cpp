#include "expressions/terms/binaryExpression.hpp"

#include "expressions/terms/variable.hpp"

#include <iostream>

namespace cas::math {

    BinaryExpression::BinaryExpression(const Expression& left, const Expression& right, bool commutative)
        : left(left.copy()), right(right.copy()), commutative(commutative) {
        this->left->parent = this;
        this->right->parent = this;
    }

    BinaryExpression::BinaryExpression(Expression* left, Expression* right, bool commutative)
        : left(assign(left, this)), right(assign(right, this)), commutative(commutative) {
    }

    BinaryExpression::~BinaryExpression() {
        delete left;
        delete right;
    }

    bool BinaryExpression::dependsOn(const Variable& var) const {
        return left->dependsOn(var) || right->dependsOn(var);
    }

    void BinaryExpression::substitute(Expression* expr, Expression* newExpr) {
        if (left == expr) {
            delete left;

            left = newExpr->copy();
            left->parent = this;
        }
        else if (right == expr) {
            delete right;

            right = newExpr->copy();
            right->parent = this;
        }
    }

    std::set<Variable> BinaryExpression::getVariables() const {
        std::set<Variable> leftVars = left->getVariables();
        std::set<Variable> rightVars = right->getVariables();

        std::set<Variable> vars = leftVars;
        vars.merge(rightVars);

        return vars;
    }

} // namespace cas::math