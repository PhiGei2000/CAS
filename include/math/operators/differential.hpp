#pragma once
#include "../expressions/expressions.hpp"

#include <stdexcept>

namespace cas::math {
    Expression* D(Expression* expr);

    Expression* D(Expression* expr, const Variable& var);

    Expression* DFunction(Function* function, const Variable& var);
} // namespace cas::math