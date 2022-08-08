#include "math/expressions/parser.hpp"

#include <sstream>

namespace cas::math {
    Expression* Parser::parseAddition(const std::string& str) {
        std::stringstream ss;

        // get first summand
        int bracketCounter = 0;
        auto it = str.begin();
        while (!(it == str.end() || ((*it) == '+' || (*it) == '-') && bracketCounter == 0)) {
            ss << *it;

            if (*it == '(')
                bracketCounter++;
            else if (*it == ')')
                bracketCounter--;

            it++;
        }

        // no addition symbol found
        if (it == str.end()) {
            return parseMultiplication(str);
        }

        // extract summands from the string
        char op = *it;

        int index = it - str.begin();
        const std::string& leftStr = ss.str();
        const std::string& rightStr = str.substr(index + 1);

        Expression* left = parseMultiplication(leftStr);
        Expression* right;
        if (op == '+') {
            right = parseAddition(rightStr);
        }
        else {
            right = new Multiplication(new Constant(-1), parseAddition(rightStr));
        }

        return new Addition(left, right);
    }

    Expression* Parser::parseMultiplication(const std::string& str) {
        std::stringstream ss;

        // get first factor
        int bracketCounter = 0;
        auto it = str.begin();
        while (!(it == str.end() || ((*it) == '*' || (*it) == '/') && bracketCounter == 0)) {
            ss << *it;
                
            if (*it == '(')
                bracketCounter++;
            else if (*it == ')')
                bracketCounter--;

            it++;
        }

        // no multiplication symbol found
        if (it == str.end()) {
            return parseExponentiation(str);
        }

        // extract factors from the string
        char op = *it;

        int index = it - str.begin();
        const std::string& leftStr = ss.str();
        const std::string& rightStr = str.substr(index + 1);

        Expression* left = parseExponentiation(leftStr);
        Expression* right;
        if (op == '*') {
            right = parseMultiplication(rightStr);
        }
        else {
            right = new Exponentiation(new Constant(-1), parseExponentiation(rightStr));
        }

        return new Multiplication(left, right);
    }

    Expression* Parser::parseExponentiation(const std::string& str) {
        std::stringstream ss;

        // get first factor
        int bracketCounter = 0;
        auto it = str.begin();
        while (!(it == str.end() || (*it) == '^' && bracketCounter == 0)) {
            ss << *it;

            if (*it == '(')
                bracketCounter++;
            else if (*it == ')')
                bracketCounter--;

            it++;
        }

        // no multiplication symbol found
        if (it == str.end()) {
            // inner expression
            if (str.front() == '(' && str.back() == ')') {
                return parseAddition(str.substr(1, str.length() - 2));
            }

            if (str.length() == 1) {
                char character = str.front();
                if (('A' <= character && character <= 'Z') || ('a' <= character && character <= 'z')) {
                    return parseVariable(str);
                }
            }

            return parseConstant(str);
        }

        // extract parts from the string
        int index = it - str.begin();
        const std::string& leftStr = ss.str();
        const std::string& rightStr = str.substr(index + 1);

        Expression* left = parseExponentiation(leftStr);
        Expression* right = parseAddition(rightStr);

        return new Exponentiation(left, right);
    }

    Variable* Parser::parseVariable(const std::string& str) {
        return new Variable(str.front());
    }

    Constant* Parser::parseConstant(const std::string& str) {
        double value = std::stod(str);

        return new Constant(value);
    }

    Expression* Parser::parse(const std::string& str) {        
        return parseAddition(str);
    }
} // namespace cas::math
