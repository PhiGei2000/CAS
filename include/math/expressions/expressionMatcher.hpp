#pragma once

#include "terms/expression.hpp"

#include "terms/variable.hpp"

#include <unordered_map>

namespace cas::math {

    struct ExpressionMatch {
        bool success;
        std::unordered_map<Variable, Expression*> variables;
    };

    class ExpressionMatcher {
      private:
        std::unordered_map<Variable, Expression*> variable_storage;

        bool matches(Expression* expr, Expression* pattern);

        void clear_variables();

      public:
        Expression* pattern;

        ExpressionMatcher(Expression* pattern);
        ~ExpressionMatcher();

        bool matches(Expression* expr);

        ExpressionMatch match(Expression* expr);
    };
} // namespace cas::math
