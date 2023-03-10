#pragma once

#include "command.hpp"

#include <mathlib/mathlib.hpp>

using namespace cas::math;

namespace cas::commands {
    static const Command<Expression> simplify = Command<Expression>(
      [](Expression* expr) {
        return expr->simplify();
      }
    );
} // namespace cas::commands