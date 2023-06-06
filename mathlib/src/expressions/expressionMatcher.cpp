#include "expressions/expressionMatcher.hpp"

#include "expressions/expressions.hpp"

namespace cas::math {
    ExpressionMatch::ExpressionMatch(bool success, Expression* node, std::map<VariableSymbol, Expression*> variables)
        : success(success), node(node) {
        for (const auto [var, expr] : variables) {
            this->variables[var] = expr->copy();
        }
    }

    ExpressionMatch::ExpressionMatch(const ExpressionMatch& other)
        : ExpressionMatch(other.success, other.node, other.variables) {
    }

    ExpressionMatch::~ExpressionMatch() {
        for (const auto [var, expr] : variables) {
            delete expr;
        }

        variables.clear();
    }

    ExpressionMatch& ExpressionMatch::operator=(const ExpressionMatch& other) {
        if (this == &other) {
            return *this;
        }

        success = other.success;
        node = other.node;
        for (const auto [var, expr] : variables) {
            delete expr;
        }
        variables.clear();

        for (const auto [var, expr] : other.variables) {
            variables[var] = expr->copy();
        }

        return *this;
    }

    ExpressionMatch ExpressionMatcher::combineMatches(const ExpressionMatch& left, const ExpressionMatch& right) {
        ExpressionMatch result = left;

        // check if the expressions for the variables are equal
        for (auto [var, expr] : right.variables) {
            if (left.variables.contains(var)) {
                ExpressionMatch varMatch = match(left.variables.at(var), expr);
                if (!varMatch.success)
                    return ExpressionMatch(false, nullptr);

                // check if the variables correspond
                for (auto [varMatchVar, varMatchExpr] : varMatch.variables) {
                    if (varMatchExpr->getType() != ExpressionTypes::Variable)
                        return ExpressionMatch(false, nullptr);

                    Variable* variable = static_cast<Variable*>(varMatchExpr);
                    if (variable->getSymbol() != varMatchVar)
                        return ExpressionMatch(false, nullptr);
                }
            }
            else {
                result.variables[var] = expr->copy();
            }
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

    ExpressionMatch ExpressionMatcher::match(Expression* expr, Expression* pattern, bool recurse, std::map<VariableSymbol, Expression*> variables) {
        switch (pattern->getType()) {
            case ExpressionTypes::Constant: {
                try {
                    Number patternValue = pattern->getValue();
                    Number value = expr->getValue();

                    return ExpressionMatch(patternValue == value, expr, {});
                }
                catch (no_value_error) {
                    return ExpressionMatch(false, nullptr);
                }
            }
            case ExpressionTypes::Variable: {
                Variable* var = static_cast<Variable*>(pattern->copy());
                if (variables.contains(var->getSymbol())) {
                    ExpressionMatch varMatch = match(expr, variables.at(var->getSymbol()), false, variables);
                    if (!varMatch.success)
                        return ExpressionMatch(false, nullptr);

                    for (auto [varMatchVar, varMatchExpr] : varMatch.variables) {
                        if (varMatchExpr->getType() != ExpressionTypes::Variable)
                            return ExpressionMatch(false, nullptr);

                        Variable* variable = static_cast<Variable*>(varMatchExpr);
                        if (variable->getSymbol() != varMatchVar)
                            return ExpressionMatch(false, nullptr);
                    }
                }

                return ExpressionMatch{true, expr, {{var->getSymbol(), expr}}};
            }
            case ExpressionTypes::Function: {
                if (expr->getType() != ExpressionTypes::Function) {
                    if (!recurse)
                        return ExpressionMatch(false, nullptr);

                    std::vector<Expression*> children = expr->getChildren();
                    for (Expression* child : children) {
                        ExpressionMatch match = ExpressionMatcher::match(child, pattern, true);
                        if (match.success) {
                            return match;
                        }
                    }
                }
            }
            default: break;
        }

        // TODO: Implement factorization i.e. 2*a matches 4*x with a=2*x, 2+a matches 1+x with a=1+x, a+x matches 2*x with a=x
        if (pattern->isBinary()) {
            if (pattern->getType() != expr->getType()) {
                if (!recurse)
                    return ExpressionMatch(false, nullptr);

                std::vector<Expression*> children = expr->getChildren();
                for (const auto child : children) {
                    ExpressionMatch match = ExpressionMatcher::match(child, pattern, true);
                    if (match.success) {
                        return match;
                    }
                }

                return ExpressionMatch(false, nullptr, {});
            }

            // if the expression types are equal expr has to be a binary expression too
            BinaryExpression* binaryPattern = dynamic_cast<BinaryExpression*>(pattern);
            BinaryExpression* binaryExpr = dynamic_cast<BinaryExpression*>(expr);

            ExpressionMatch leftMatch = match(binaryExpr->left, binaryPattern->left, false, variables);
            std::map<VariableSymbol, Expression*> combinedVars = variables;
            combinedVars.insert(leftMatch.variables.begin(), leftMatch.variables.end());
            ExpressionMatch rightMatch = match(binaryExpr->right, binaryPattern->right, false, combinedVars);

            if (leftMatch.success && rightMatch.success) {
                ExpressionMatch result = combineMatches(leftMatch, rightMatch);

                if (result.success) {
                    result.node = expr;
                    return result;
                }
            }

            // if no match found check swapped expression
            if (binaryPattern->commutative) {
                leftMatch = match(binaryExpr->left, binaryPattern->right, false, variables);
                combinedVars = variables;
                combinedVars.insert(leftMatch.variables.begin(), leftMatch.variables.end());
                rightMatch = match(binaryExpr->right, binaryPattern->left, false, combinedVars);

                if (leftMatch.success && rightMatch.success) {
                    ExpressionMatch result = combineMatches(leftMatch, rightMatch);

                    if (result.success) {
                        result.node = expr;
                        return result;
                    }
                }

                if (binaryExpr->left->getType() == expr->getType()) {
                    BinaryExpression* leftSwap = static_cast<BinaryExpression*>(binaryExpr->copy());
                    BinaryExpression* leftChild = static_cast<BinaryExpression*>(leftSwap->left);
                    leftSwap->right = assign(static_cast<BinaryExpression*>(binaryExpr->left)->right, leftSwap);
                    leftChild->right = assign(binaryExpr->right, leftChild);

                    ExpressionMatch match = ExpressionMatcher::match(leftSwap, pattern, recurse, variables);
                    delete leftSwap;
                    if (match.success)
                        return match;
                }

                if (binaryExpr->right->getType() == expr->getType()) {
                    BinaryExpression* rightSwap = static_cast<BinaryExpression*>(binaryExpr->copy());
                    BinaryExpression* rightChild = static_cast<BinaryExpression*>(rightSwap->right);
                    rightSwap->left = assign(static_cast<BinaryExpression*>(binaryExpr->right)->left, rightSwap);
                    rightChild->left = assign(binaryExpr->left, rightChild);

                    ExpressionMatch match = ExpressionMatcher::match(rightSwap, pattern, recurse, variables);
                    delete rightSwap;
                    if (match.success)
                        return match;
                }
            }
        }

        return ExpressionMatch(false, nullptr);
    }

    std::vector<ExpressionMatch> ExpressionMatcher::matchAll(Expression* expr, Expression* pattern) {
        ExpressionMatch thisMatch = match(expr, pattern);

        if (thisMatch.success) {
            return std::vector<ExpressionMatch>({thisMatch});
        }

        std::vector<Expression*> children = expr->getChildren();
        std::vector<ExpressionMatch> result;
        for (Expression* child : children) {
            std::vector<ExpressionMatch> subMatch = matchAll(child, pattern);

            result.insert(result.end(), subMatch.begin(), subMatch.end());
        }

        return result;
    }

    Expression* ExpressionMatcher::substitute(Expression* expr, Expression* pattern, Expression* substitution) {
        Expression* result = expr->copy();
        std::vector<ExpressionMatch> matches = ExpressionMatcher::matchAll(result, pattern);

        for (auto match : matches) {
            if (match.success) {
                Expression* subs = substitution->copy();

                for (auto [var, value] : match.variables) {
                    if (subs->getType() == ExpressionTypes::Variable) {
                        delete subs;
                        subs = value->copy();
                    }
                    else {
                        Variable v = Variable(var);
                        subs->setVariable(&v, value);
                    }
                }

                if (result == match.node) {
                    delete result;

                    result = subs;
                }
                else {
                    result->replace(match.node, subs);
                    delete subs;
                }
            }
        }

        return result;
    }
} // namespace cas::math