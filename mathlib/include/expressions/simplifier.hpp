#pragma once
#include "expressions.hpp"

#include <vector>

namespace cas::math {
    class Simplifier {
        protected:
            struct ReplaceRule {
                Expression* pattern;
                Expression* newValue;
            };

            static std::vector<ReplaceRule> replaceRules;

        public:
            static Expression* simplify(const Expression* expr);
    };
}