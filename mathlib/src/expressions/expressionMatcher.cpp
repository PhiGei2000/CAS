#include "expressions/expressionMatcher.hpp"

#include "expressions/expressions.hpp"

namespace cas::math {
    ExpressionMatch::ExpressionMatch(bool success, std::map<Variable*, Expression*> variables)
        : success(success) {
        for (const auto [var, expr] : variables) {
            this->variables[static_cast<Variable*>(var->copy())] = expr->copy();
        }
    }

    ExpressionMatch::ExpressionMatch(const ExpressionMatch& other)
        : ExpressionMatch(other.success, other.variables) {
    }

    ExpressionMatch::~ExpressionMatch() {
        for (const auto [var, expr] : variables) {
            delete var;
            delete expr;
        }

        variables.clear();
    }

    ExpressionMatch& ExpressionMatch::operator=(const ExpressionMatch& other) {
        if (this == &other) {
            return *this;
        }

        success = other.success;
        for (const auto [var, expr] : variables) {
            delete var;
            delete expr;
        }
        variables.clear();

        for (const auto [var, expr] : other.variables) {
            variables[static_cast<Variable*>(var->copy())] = expr->copy();
        }

        return *this;
    }

    ExpressionMatch operator&(const ExpressionMatch& left, const ExpressionMatch& right) {
        ExpressionMatch result = left;

        for (const auto [var, expr] : right.variables) {
            if (result.variables.contains(var)) {
                // TODO: Add multi variable occurence in patterns
                std::__throw_logic_error("A variable occures twice in a pattern");
            }

            result.variables[static_cast<Variable*>(var->copy())] = expr->copy();
        }

        return result;
    }

    bool ExpressionMatcher::matches(Expression* expr, Expression* pattern) {
        switch (pattern->getType()) {
            case ExpressionTypes::Constant: {
                try {
                    return expr->getValue() == pattern->getValue();
                }
                catch (no_value_error) {
                    return false;
                }
            }
            case ExpressionTypes::Variable: return true;
            default: break;
        }

        if (pattern->isBinary()) {
            if (pattern->getType() != expr->getType()) {
                return false;
            }

            // if the expression types are equal expr has to be a binary expression too
            BinaryExpression* binaryPattern = dynamic_cast<BinaryExpression*>(pattern);
            BinaryExpression* binaryExpr = dynamic_cast<BinaryExpression*>(expr);

            if (binaryPattern->commutative) {
                return matches(binaryExpr->left, binaryPattern->left) && matches(binaryExpr->right, binaryPattern->right) ||
                       matches(binaryExpr->left, binaryPattern->right) && matches(binaryExpr->right, binaryPattern->left);
            }
            else {
                return matches(binaryExpr->left, binaryPattern->left) && matches(binaryExpr->right, binaryPattern->right);
            }
        }

        return false;
    }

    ExpressionMatch ExpressionMatcher::match(Expression* expr, Expression* pattern, bool recurse) {
        // TODO: Add function matching
        switch (pattern->getType()) {
            case ExpressionTypes::Constant: {
                try {
                    return ExpressionMatch(expr->getValue() == pattern->getValue());
                }
                catch (no_value_error) {
                    return ExpressionMatch(false);
                }
            }
            case ExpressionTypes::Variable: {
                Variable* var = dynamic_cast<Variable*>(pattern->copy());
                return ExpressionMatch{true, {{var, expr}}};
            }
            default: break;
        }

        if (pattern->isBinary()) {
            if (pattern->getType() != expr->getType()) {
                if (!recurse)
                    return ExpressionMatch(false);

                std::vector<Expression*> children = expr->getChildren();
                for (const auto child : children) {
                    ExpressionMatch match = ExpressionMatcher::match(child, pattern, true);
                    if (match.success) {
                        return match;
                    }
                }

                return false;
            }

            // if the expression types are equal expr has to be a binary expression too
            BinaryExpression* binaryPattern = dynamic_cast<BinaryExpression*>(pattern);
            BinaryExpression* binaryExpr = dynamic_cast<BinaryExpression*>(expr);

            ExpressionMatch leftMatch = match(binaryExpr->left, binaryPattern->left);
            ExpressionMatch rightMatch = match(binaryExpr->right, binaryPattern->right);

            if (leftMatch.success && rightMatch.success) {
                return leftMatch & rightMatch;
            }

            if (binaryPattern->commutative) {
                leftMatch = match(binaryExpr->left, binaryPattern->right);
                rightMatch = match(binaryExpr->right, binaryPattern->left);

                if (leftMatch.success && rightMatch.success) {
                    return leftMatch & rightMatch;
                }
            }
        }

        return ExpressionMatch(false);
    }

    Expression* ExpressionMatcher::substitute(Expression* expr, Expression* pattern, Expression* substitution) {
    }
} // namespace cas::math