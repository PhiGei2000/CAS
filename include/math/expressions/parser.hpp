#pragma once

#include "../expressions.hpp"

namespace cas::math {
    class Parser {
        private:
            static Expression* parseAddition(const std::string& str);
            static Expression* parseMultiplication(const std::string& str);
            static Expression* parseExponentiation(const std::string& str);

            static Variable* parseVariable(const std::string& str);
            static Constant* parseConstant(const std::string& str);

        public:
            static Expression* parse(const std::string& str);
    };
}