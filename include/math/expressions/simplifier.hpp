#pragma once

#include "../expressions.hpp"

namespace cas::math
{
    class Simplifier {
        public:
          static Expression* simplify(const Expression* expr);

          static Expression* simplifyAddition(const Addition* sum);
          static Expression* simplifyMultiplication(const Multiplication* product);
    };
} // namespace cas::math
