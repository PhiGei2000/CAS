#pragma once
#include "command.hpp"

#include <mathlib/mathlib.hpp>

using namespace cas::math;

namespace cas::commands {
    Command<ExpressionMatch, Expression*, Expression*> matchCommand = Command<ExpressionMatch, Expression*, Expression*>(
        [](Engine* engine, Expression* expr, Expression* pattern) {
            return ExpressionMatcher::match(expr, pattern);
        });

    Command<ExpressionMatch, Expression*, Expression*> matchRecurseCommand = Command<ExpressionMatch, Expression*, Expression*>(
        [](Engine* engine, Expression* expr, Expression* pattern) {
            return ExpressionMatcher::match(expr, pattern, true);
        });

    Command<Expression*, Expression*, Expression*, Expression*> substituteCommand = Command<Expression*, Expression*, Expression*, Expression*>(
        [](Engine* engine, Expression* expr, Expression* pattern, Expression* substitution) {
            return ExpressionMatcher::substitute(expr, pattern, substitution);
        });

    Command<std::vector<ExpressionMatch>, Expression*, Expression*> matchAllCommand = Command<std::vector<ExpressionMatch>, Expression*, Expression*>(
        [](Engine* engine, Expression* expr, Expression* pattern) {
            return ExpressionMatcher::matchAll(expr, pattern);
        });
} // namespace cas::commands
