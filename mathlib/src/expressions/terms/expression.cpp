#include "expressions/terms/expression.hpp"

#include "expressions/expressions.hpp"

namespace cas::math {
    no_value_error::no_value_error(const std::string& message)
        : std::runtime_error(message) {
    }

    Expression::~Expression() {
    }

    std::vector<Expression*> Expression::getChildren() const {
        return {};
    }

    Expression* Expression::simplify() const {
        return this->copy();
    }

    void Expression::substitute(Expression* expr, Expression* newExpr) {
    }

    Expression* assign(Expression* other, Expression* parent) {
        Expression* expr;
        if (other->parent == nullptr || other->parent == parent) {
            expr = other;
        }
        else {
            expr = other->copy();
        }
        expr->parent = parent;
        return expr;
    }

} // namespace cas::math