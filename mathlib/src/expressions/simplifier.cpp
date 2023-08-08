#include "expressions/simplifier.hpp"

#include "expressions/expressionMatcher.hpp"

namespace cas::math {
    std::vector<Simplifier::ReplaceRule> Simplifier::replaceRules = {
        ReplaceRule{new Multiplication(new Number(0), new Variable("x")), new Number(0)},
        ReplaceRule{new Multiplication(new Number(1), new Variable("x")), new Variable("x")},
        ReplaceRule{new Addition(new Number(0), new Variable("x")), new Variable("x")},
    };

    Expression* Simplifier::simplify(const Expression* expr) {
        Expression* result = expr->copy();

        for (const ReplaceRule rule : replaceRules) {
            Expression* tmp = ExpressionMatcher::substitute(result, rule.pattern, rule.newValue);

            delete result;
            result = tmp;
        }

        return result;
    }
} // namespace cas::math