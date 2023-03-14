#pragma once

#include "terms/expression.hpp"

#include "terms/variable.hpp"

#include <map>

namespace cas::math {
    struct ExpressionMatch {
        bool success;
        std::map<Variable*, Expression*> variables;

        ExpressionMatch(bool success, std::map<Variable*, Expression*> variables = {});
        ExpressionMatch(const ExpressionMatch& other);
        ~ExpressionMatch();

        ExpressionMatch& operator=(const ExpressionMatch& other);
    };

    ExpressionMatch operator&(const ExpressionMatch& left, const ExpressionMatch& right);

    class ExpressionMatcher {        
      public:        
        static bool matches(Expression* expr, Expression* pattern);

        static ExpressionMatch match(Expression* expression, Expression* pattern, bool recurse = false);        
        
        static Expression* substitute(Expression* expr, Expression* pattern, Expression* substitution);
    };
} // namespace cas::math
