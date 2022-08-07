#pragma once
#include "expressions.hpp"

#include <stdexcept>

namespace cas::math {
    Expression* D(Expression* expr, const Variable& var);

    Expression* DFunction(Function* function, const Variable& var);
} // namespace cas::math