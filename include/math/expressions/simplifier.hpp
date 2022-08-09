#pragma once

#include "../expressions.hpp"

#include <unordered_map>
#include <vector>

namespace cas::math {
    class Simplifier {
      private:
        struct ProductParts {
            double coefficient = 1;
            std::unordered_map<char, double> variables = {};
            std::vector<Expression*> restTerms = {};

            void multiply(const ProductParts& parts);
            void power(double exp);

            static bool areLike(const ProductParts& first, const ProductParts& second);            
        };

        static ProductParts getProductParts(const Multiplication* prod) noexcept(false);
        static ProductParts getExpProductParts(const Exponentiation* exp) noexcept(false);

        static Expression* getProductFromParts(const ProductParts& parts );

        static void getSummands(const Expression* sum, std::vector<Expression*>* summands);

      public:
        static Expression* multiplyOut(const Expression* left, const Expression* right);
        static Expression* simplify(const Expression* expr);

        static Expression* simplifyAddition(const Addition* sum);
        static Expression* simplifyMultiplication(const Multiplication* product);
        static Expression* simplifyExponentiation(const Exponentiation* exp);
    };
} // namespace cas::math
