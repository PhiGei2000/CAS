#pragma once

#include "terms/expression.hpp"

#include "terms/variable.hpp"

#include <map>

namespace cas::math {
    struct ExpressionMatch {
        bool success;
        std::map<VariableSymbol, Expression*> variables;
        Expression* node;

        ExpressionMatch(bool success, Expression* node, std::map<VariableSymbol, Expression*> variables = {});
        ExpressionMatch(const ExpressionMatch& other);
        ~ExpressionMatch();

        ExpressionMatch& operator=(const ExpressionMatch& other);
    };

    class ExpressionMatcher {
      protected:
        static ExpressionMatch combineMatches(const ExpressionMatch& first, const ExpressionMatch& second);

      public:
        static bool matches(Expression* expr, Expression* pattern);

        static ExpressionMatch match(Expression* expression, Expression* pattern, bool recurse = false, std::map<VariableSymbol, Expression*> variables = {});

        static std::vector<ExpressionMatch> matchAll(Expression* expression, Expression* pattern);

        static Expression* substitute(Expression* expr, Expression* pattern, Expression* substitution);
    };
} // namespace cas::math
