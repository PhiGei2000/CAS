#pragma once

#include "expressions.hpp"

#include "terms/variable.hpp"

#include <map>

namespace cas::math {
    struct BinaryExpression;

    struct ExpressionMatch {
        bool success;
        std::map<VariableSymbol, Expression*> variables;
        Expression* match;
        Expression* matchedNode;

        ExpressionMatch(bool success, Expression* node, std::map<VariableSymbol, Expression*> variables = {});
        ExpressionMatch(const ExpressionMatch& other);
        ~ExpressionMatch();

        void setMatchNode(Expression* matchNode);

        ExpressionMatch& operator=(const ExpressionMatch& other);
    };

    class ExpressionMatcher {
      protected:
        static ExpressionMatch combineMatches(const ExpressionMatch& first, const ExpressionMatch& second);

        template<ExpressionType T>
        static bool matchExpression(Expression* expr, const Expression* pattern, ExpressionMatch& result, std::map<VariableSymbol, Expression*> variables = {}, bool recurse = false);

        static ExpressionMatch matchBinaryExpression(BinaryExpression* expr, const BinaryExpression* pattern, std::map<VariableSymbol, Expression*> variables = {}, bool swap = false);

        static ExpressionMatch matchBinaryExpressionConstant(Expression* expr, const Expression* pattern, ExpressionTypes type, VariableSymbol var, std::map<VariableSymbol, Expression*> variables = {});

      public:
        static bool matches(Expression* expr, const Expression* pattern);

        static ExpressionMatch match(Expression* expression, const Expression* pattern, bool recurse = false, std::map<VariableSymbol, Expression*> variables = {});

        static std::vector<ExpressionMatch> matchAll(Expression* expression, const Expression* pattern);

        static Expression* substitute(Expression* expr, const Expression* pattern, Expression* substitution);
    };
} // namespace cas::math
