#include "math/expressions/terms/expression.hpp"

#include "math/expressions/terms/variable.hpp"

namespace cas::math {
    no_value_error::no_value_error(const std::string& message)
        : std::runtime_error(message) {
    }

    Expression::~Expression() {
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