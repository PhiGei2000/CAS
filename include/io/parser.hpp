#pragma once
#include <mathlib/mathlib.hpp>

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
            static Number* parseConstant(const std::string& str);

            static Expression* parseFunction(const std::string& str);

            static std::string getBracketContent(const std::string& str, int begin = 0);
            static std::string getBracketContent(const std::string& str, std::string::const_iterator it);
                        
            template<const char... operatorSymbols>
            inline static std::tuple<std::string, std::string, char> parseOperation(const std::string& str) {
                std::stringstream ss;

                int bracketCounter = 0;
                auto it = str.begin();
                while (!(it == str.end() || ((*it == operatorSymbols) || ...)) && bracketCounter == 0) {
                    ss << *it;

                    if (*it == '(')
                        bracketCounter++;
                    else if (*it == ')')
                        bracketCounter--;

                    it++;
                }

                if (it == str.end()) {
                    return std::tuple{str, "", '\0'};
                }

                int index = it - str.begin();
                return std::tuple<std::string, std::string, char>{ss.str(), str.substr(index + 1), *it};
            }

        public:
            static Expression* parse(const std::string& str);
    };
}