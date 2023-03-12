#pragma once

#include "command.hpp"

#include <mathlib/mathlib.hpp>

using namespace cas::math;

namespace cas {
    class Engine;

    namespace commands {
        static const Command<Expression*, Expression*> simplify = Command<Expression*, Expression*>(
            [](Engine* engine, Expression* expr) {
                return expr->simplify();
            });
    }
} // namespace cas