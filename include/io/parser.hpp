#pragma once

#include "math/expressions/expressions.hpp"

namespace cas::math {
    class Parser {
        private:
            static Expression* parseAddition(const std::string& str);
            static Expression* parseMultiplication(const std::string& str);
            static Expression* parseExponentiation(const std::string& str);

            static Expression* parseSymbol(const std::string& str);
            static Constant* parseConstant(const std::string& str);

            static Function* parseFunction(const std::string& str);

            static std::string getBracketContent(const std::string& str, int begin = 0);
            static std::string getBracketContent(const std::string& str, std::string::const_iterator it);

        public:
            static Expression* parse(const std::string& str);
    };
}