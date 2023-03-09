#pragma once

#include "expressions/expressions.hpp"

#include <regex>

using namespace cas::math;

namespace cas::io {
    class Parser {
        private:
            static const std::regex numberRegex;

            static Expression* parseAddition(const std::string& str);
            static Expression* parseMultiplication(const std::string& str);
            static Expression* parseDivision(const std::string& str);
            static Expression* parseExponentiation(const std::string& str);

            static Expression* parseSymbol(const std::string& str);
            static Constant* parseConstant(const std::string& str);

            static Expression* parseFunction(const std::string& str);

            static std::string getBracketContent(const std::string& str, int begin = 0);
            static std::string getBracketContent(const std::string& str, std::string::const_iterator it);

        public:
            static Expression* parse(const std::string& str);
    };
}