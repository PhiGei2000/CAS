#include "math/expressions/expressionMatcher.hpp"

#include "math/expressions/terms/binaryExpression.hpp"

namespace cas::math {
    ExpressionMatcher::ExpressionMatcher(Expression* pattern)
        : pattern(pattern) {
        const std::set<Variable> vars = pattern->getVariables();
        for (const Variable& var : vars) {
            variable_storage[var] = nullptr;
        }
    }

    ExpressionMatcher::~ExpressionMatcher() {
        delete pattern;

        for (const auto [var, expr] : variable_storage) {
            delete expr;
        }
    }

    bool ExpressionMatcher::matches(Expression* expr, Expression* pattern) {
        // check if both expressions are numeric and have the same value
        try {
            if (expr->getValue() == pattern->getValue())
                return true;
        }
        catch (no_value_error) {
        }

        if (pattern->getType() == ExpressionTypes::Variable) {
            Variable* patternVar = reinterpret_cast<Variable*>(pattern);            

            if (variable_storage[*patternVar] == nullptr) {
                variable_storage[*patternVar] = expr->copy();
                return true;
            }

            return matches(expr, variable_storage[*patternVar]);
        }

        // check if both expressions have the same type
        if (expr->getType() != pattern->getType())
            return false;

        // check if pattern contains a binary expression
        BinaryExpression* binaryPattern = dynamic_cast<BinaryExpression*>(pattern);
        if (binaryPattern != nullptr) {

            // check if expr is also binary
            BinaryExpression* binaryExpr = dynamic_cast<BinaryExpression*>(expr);
            if (binaryExpr == nullptr)
                return false;

            // check expression recursive
            if (matches(binaryExpr->left, binaryPattern->left) && matches(binaryExpr->right, binaryPattern->right))
                return true;

            if (binaryPattern->commutative) {
                if (matches(binaryExpr->left, binaryPattern->right) && matches(binaryExpr->right, binaryPattern->left))
                    return true;
            }
        }

        return false;
    }

    void ExpressionMatcher::clear_variables() {
        for (auto [var, _] : variable_storage) {
            delete variable_storage[var];
            variable_storage[var] = nullptr;
        }
    }

    bool ExpressionMatcher::matches(Expression* expr) {
        clear_variables();

        return matches(expr, pattern);
    }

    ExpressionMatch ExpressionMatcher::match(Expression* expr) {
        clear_variables();

        bool success = matches(expr);

        return ExpressionMatch{success, variable_storage};
    }

    void ExpressionMatcher::replace(Expression* expr, Expression* subexpr) {
        if (matches(expr)) {
            Expression* parent = expr->parent;
            parent->substitute(expr, subexpr);

            return;
        }
    }
} // namespace cas::math
