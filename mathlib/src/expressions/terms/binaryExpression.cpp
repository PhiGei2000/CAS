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

    std::vector<Expression*> BinaryExpression::getChildren() const {
        return {left, right};
    }

    bool BinaryExpression::dependsOn(const Variable& var) const {
        return left->dependsOn(var) || right->dependsOn(var);
    }

    void BinaryExpression::replace(Expression* expr, Expression* newExpr) {
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
        else {
            left->replace(expr, newExpr);
            right->replace(expr, newExpr);
        }
    }

    void BinaryExpression::setVariable(Variable* var, Expression* expr) {
        if (left->getType() == ExpressionTypes::Variable) {
            Variable* leftVar = static_cast<Variable*>(left);
            if (*leftVar == *var) {
                delete left;

                left = expr->copy();
                left->parent = this;
            }
        }
        else {
            left->setVariable(var, expr);
        }

        if (right->getType() == ExpressionTypes::Variable) {
            Variable* rightVar = static_cast<Variable*>(right);
            if (*rightVar == *var) {
                delete right;

                right = expr->copy();
                right->parent = this;
            }
        }
        else {
            right->setVariable(var, expr);
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