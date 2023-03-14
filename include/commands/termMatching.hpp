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
        }
    );
}
