#include "expressions/expressionMatcher.hpp"

#include "expressions/expressions.hpp"

namespace cas::math {
    ExpressionMatch::ExpressionMatch(bool success, Expression* node, std::map<VariableSymbol, Expression*> variables)
        : success(success), matchedNode(node) {
        if (node != nullptr)
            match = node->copy();
        else
            match = nullptr;

        for (const auto [var, expr] : variables) {
            this->variables[var] = expr->copy();
        }
    }

    ExpressionMatch::ExpressionMatch(const ExpressionMatch& other)
        : ExpressionMatch(other.success, other.matchedNode, other.variables) {
    }

    ExpressionMatch::~ExpressionMatch() {
        for (const auto [var, expr] : variables) {
            delete expr;
        }

        variables.clear();

        if (match != nullptr) {
            delete match;
        }
    }

    void ExpressionMatch::setMatchNode(Expression* matchedNode) {
        if (match != nullptr)
            delete match;

        match = matchedNode->copy();
        this->matchedNode = matchedNode;
    }

    ExpressionMatch& ExpressionMatch::operator=(const ExpressionMatch& other) {
        if (this == &other) {
            return *this;
        }

        success = other.success;
        match = other.match != nullptr ? other.match->copy() : nullptr;
        matchedNode = other.matchedNode;
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

    bool ExpressionMatcher::matches(Expression* expr, const Expression* pattern) {
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
            const BinaryExpression* binaryPattern = dynamic_cast<const BinaryExpression*>(pattern);
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

    template<>
    bool ExpressionMatcher::matchExpression<Number>(Expression* expr, const Expression* pattern, ExpressionMatch& result, std::map<VariableSymbol, Expression*> variables, bool recurse) {
        try {
            Number patternValue = pattern->getValue();
            Number value = expr->getValue();

            result = ExpressionMatch(patternValue == value, expr, {});
        }
        catch (no_value_error) {
            result = ExpressionMatch(false, nullptr);
        }

        return true;
    }

    template<>
    bool ExpressionMatcher::matchExpression<Variable>(Expression* expr, const Expression* pattern, ExpressionMatch& result, std::map<VariableSymbol, Expression*> variables, bool recurse) {
        Variable* var = static_cast<Variable*>(pattern->copy());
        if (variables.contains(var->getSymbol())) {
            ExpressionMatch varMatch = match(expr, variables.at(var->getSymbol()), false, variables);
            if (!varMatch.success)
                result = ExpressionMatch(false, nullptr);

            for (auto [varMatchVar, varMatchExpr] : varMatch.variables) {
                if (varMatchExpr->getType() != ExpressionTypes::Variable)
                    result = ExpressionMatch(false, nullptr);

                Variable* variable = static_cast<Variable*>(varMatchExpr);
                if (variable->getSymbol() != varMatchVar)
                    result = ExpressionMatch(false, nullptr);
            }
        }
        else {
            result = ExpressionMatch{true, expr, {{var->getSymbol(), expr->copy()}}};
        }
        return true;
    }

    template<>
    bool ExpressionMatcher::matchExpression<NamedConstant>(Expression* expr, const Expression* pattern, ExpressionMatch& result, std::map<VariableSymbol, Expression*> variables, bool recurse) {
        const NamedConstant* patternC = reinterpret_cast<const NamedConstant*>(pattern);
        switch (expr->getType()) {
            case ExpressionTypes::NamedConstant: {
                NamedConstant* c = reinterpret_cast<NamedConstant*>(expr);

                result = ExpressionMatch(*patternC == *c, expr);
            } break;
            case ExpressionTypes::Constant: {
                Number* number = reinterpret_cast<Number*>(expr);

                result = ExpressionMatch(patternC->getValue() == number->getValue(), expr);
            } break;
            default:
                return false;
        }

        return true;
    }

    template<>
    bool ExpressionMatcher::matchExpression<BaseFunction>(Expression* expr, const Expression* pattern, ExpressionMatch& result, std::map<VariableSymbol, Expression*> variables, bool recurse) {
        const BaseFunction* patternF = reinterpret_cast<const BaseFunction*>(pattern);
        if (expr->getType() != ExpressionTypes::Function) {
            if (!recurse) {
                result = ExpressionMatch(false, nullptr);
                return true;
            }

            std::vector<Expression*> children = expr->getChildren();
            for (Expression* child : children) {
                ExpressionMatch match = ExpressionMatcher::match(child, pattern, true);
                if (match.success) {
                    result = match;
                    return true;
                }
            }
        }
        else {
            BaseFunction* f = reinterpret_cast<BaseFunction*>(expr);

            if (f->name == patternF->name) {
                const std::vector<Expression*> patternArgs = patternF->getChildren();
                const std::vector<Expression*> args = f->getChildren();
                std::map<VariableSymbol, Expression*> vars = variables;

                for (int i = 0; i < patternArgs.size(); i++) {
                    auto match = ExpressionMatcher::match(args[i], patternArgs[i], false, vars);

                    if (match.success) {
                        for (const auto [var, varExp] : match.variables) {
                            vars[var] = varExp->copy();
                        }
                    }
                    else {
                        result = ExpressionMatch(false, nullptr);
                        return true;
                    }
                }

                result = ExpressionMatch(true, expr, vars);
                return true;
            }
        }

        return false;
    }

    ExpressionMatch ExpressionMatcher::match(Expression* expr, const Expression* pattern, bool recurse, std::map<VariableSymbol, Expression*> variables) {
        ExpressionMatch result = ExpressionMatch{false, nullptr};
        switch (pattern->getType()) {
            case ExpressionTypes::Constant:
                if (matchExpression<Number>(expr, pattern, result))
                    return result;
                break;
            case ExpressionTypes::Variable:
                if (matchExpression<Variable>(expr, pattern, result, variables))
                    return result;
                break;
            case ExpressionTypes::NamedConstant:
                if (matchExpression<NamedConstant>(expr, pattern, result))
                    return result;
                break;
            case ExpressionTypes::Function:
                if (matchExpression<BaseFunction>(expr, pattern, result))
                    return result;
                break;

            default: break;
        }

        // TODO: Implement factorization i.e. 2*a matches 4*x with a=2*x, 2+a matches 1+x with a=1+x, a+x matches 2*x with a=x
        if (pattern->isBinary()) {
            const BinaryExpression* binaryPattern = dynamic_cast<const BinaryExpression*>(pattern);
            if (pattern->getType() != expr->getType()) {
                if (expr->getType() == ExpressionTypes::Constant) {
                    if (binaryPattern->left->getType() == ExpressionTypes::Variable && binaryPattern->right->getType() == ExpressionTypes::Constant) {
                        VariableSymbol var = reinterpret_cast<const Variable*>(binaryPattern->left)->getSymbol();
                        return matchBinaryExpressionConstant(expr, binaryPattern->right, pattern->getType(), var, variables);
                    }
                    else if (binaryPattern->left->getType() == ExpressionTypes::Constant && binaryPattern->right->getType() == ExpressionTypes::Variable) {
                        VariableSymbol var = reinterpret_cast<const Variable*>(binaryPattern->right)->getSymbol();
                        return matchBinaryExpressionConstant(expr, binaryPattern->left, pattern->getType(), var, variables);
                    }
                }

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
            BinaryExpression* binaryExpr = dynamic_cast<BinaryExpression*>(expr);
            ExpressionMatch result = matchBinaryExpression(binaryExpr, binaryPattern, variables);
            if (result.success) {
                return result;
            }

            // if no match found check swapped expression
            if (binaryPattern->commutative) {
                ExpressionMatch result = matchBinaryExpression(binaryExpr, binaryPattern, variables, true);
                if (result.success) {
                    return result;
                }

                if (recurse) {
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
        }

        return ExpressionMatch(false, nullptr);
    }

    ExpressionMatch ExpressionMatcher::matchBinaryExpression(BinaryExpression* expr, const BinaryExpression* pattern, std::map<VariableSymbol, Expression*> variables, bool swap) {
        Expression *left, *right;
        Expression* patternLeft = pattern->left;
        Expression* patternRight = pattern->right;

        if (swap) {
            left = expr->right;
            right = expr->left;
        }
        else {
            left = expr->left;
            right = expr->right;
        }

        ExpressionMatch leftMatch = match(left, patternLeft, false, variables);
        std::map<VariableSymbol, Expression*> combinedVars = variables;
        combinedVars.insert(leftMatch.variables.begin(), leftMatch.variables.end());
        ExpressionMatch rightMatch = match(right, patternRight, false, combinedVars);
        ExpressionMatch result = combineMatches(leftMatch, rightMatch);

        if (leftMatch.success && rightMatch.success) {
            result.setMatchNode(left->parent);
            return result;
        }
        else if (leftMatch.success) {
            if (right->getType() == ExpressionTypes::Constant && patternRight->getType() == ExpressionTypes::Constant && patternLeft->getType() == ExpressionTypes::Variable) {
                VariableSymbol var = reinterpret_cast<const Variable*>(patternLeft)->getSymbol();
                return matchBinaryExpressionConstant(right, patternRight, expr->getType(), var, result.variables);
            }
        }
        else if (rightMatch.success) {
            if (left->getType() == ExpressionTypes::Constant && patternLeft->getType() == ExpressionTypes::Constant && patternRight->getType() == ExpressionTypes::Variable) {
                VariableSymbol var = reinterpret_cast<const Variable*>(patternRight)->getSymbol();
                return matchBinaryExpressionConstant(left, patternLeft, expr->getType(), var, result.variables);
            }
        }

        return ExpressionMatch{false, nullptr};
    }

    ExpressionMatch ExpressionMatcher::matchBinaryExpressionConstant(Expression* expr, const Expression* pattern, ExpressionTypes type, VariableSymbol var, std::map<VariableSymbol, Expression*> variables) {
        Number expressionValue = expr->getValue();
        Number patternValue = pattern->getValue();

        switch (type) {
            case ExpressionTypes::Addition: {
                Number* summand = new Number(expressionValue - patternValue);

                if (variables[var] == nullptr)
                    variables[var] = summand;
                else
                    variables[var] = new Addition(summand, variables[var]);
                return ExpressionMatch{true, expr->parent == nullptr ? expr : expr->parent, variables};

            } break;
            case ExpressionTypes::Multiplication: {
                if (patternValue != 0) {
                    Number* factor = new Number(expressionValue / patternValue);
                    if (variables[var] == nullptr)
                        variables[var] = factor;
                    else
                        variables[var] = new Multiplication(factor, variables[var]);

                    return ExpressionMatch{true, expr->parent == nullptr ? expr : expr->parent, variables};
                }
            } break;
        }

        return ExpressionMatch{false, nullptr};
    }

    std::vector<ExpressionMatch> ExpressionMatcher::matchAll(Expression* expr, const Expression* pattern) {
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

    Expression* ExpressionMatcher::substitute(Expression* expr, const Expression* pattern, Expression* substitution) {
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

                if (result == match.matchedNode) {
                    delete result;

                    result = subs;
                }
                else {
                    result->replace(match.matchedNode, subs);
                    delete subs;
                }
            }
        }

        return result;
    }
} // namespace cas::math