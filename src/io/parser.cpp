#include "io/parser.hpp"

#include <sstream>

using namespace cas::math;

namespace cas::io {
    Expression* Parser::parseAddition(const std::string& str) {
        std::stringstream ss;

        // get first summand
        int bracketCounter = 0;
        auto it = str.begin();
        while (!(it == str.end() || ((*it) == '+' || ((*it) == '-' && it != str.begin())) && bracketCounter == 0)) {
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
        while (!(it == str.end() || (*it) == '*' && bracketCounter == 0)) {
            ss << *it;

            if (*it == '(')
                bracketCounter++;
            else if (*it == ')')
                bracketCounter--;

            it++;
        }

        // no multiplication symbol found
        if (it == str.end()) {
            return parseDivision(str);
        }

        // extract factors from the string        
        int index = it - str.begin();
        const std::string& leftStr = ss.str();
        const std::string& rightStr = str.substr(index + 1);

        // create result
        Expression* left = parseDivision(leftStr);
        Expression* right = parseMultiplication(rightStr);

        return new Multiplication(left, right);
    }

    Expression* Parser::parseDivision(const std::string& str) {
        std::stringstream ss;
        auto it = str.begin();
        int bracketCounter = 0;

        while (!(it == str.end() || (*it) == '/' && bracketCounter == 0)) {
            ss << *it;

            if (*it == '(')
                bracketCounter++;
            else if (*it == ')')
                bracketCounter--;

            it++;
        }

        if (it == str.end()) {
            return parseExponentiation(str);
        }

        int index = it - str.begin();
        std::string leftStr = ss.str();
        std::string rightStr = str.substr(index + 1);

        Expression* left = parseExponentiation(leftStr);
        Expression* right = new Exponentiation(parseExponentiation(rightStr), new Constant(-1));

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

        // no exponentiation symbol found
        if (it == str.end()) {
            // inner expression
            if (str.front() == '(' && str.back() == ')') {
                return parseAddition(str.substr(1, str.length() - 2));
            }

            if (str.length() == 1) {
                char character = str.front();
                if (('A' <= character && character <= 'Z') || ('a' <= character && character <= 'z')) {
                    return parseSymbol(str);
                }
            }

            char front = str.front();
            if ((front <= '9' && front >= '0') || front == '-') {
                return parseConstant(str);
            }
            else {
                return parseFunction(str);
            }
        }

        // extract parts from the string
        int index = it - str.begin();
        const std::string& leftStr = ss.str();
        const std::string& rightStr = str.substr(index + 1);

        Expression* left = parseExponentiation(leftStr);
        Expression* right = parseAddition(getBracketContent(rightStr));

        return new Exponentiation(left, right);
    }

    Expression* Parser::parseSymbol(const std::string& str) {
        if (str == "e") {
            return new E();
        }

        return new Variable(str.front());
    }

    Constant* Parser::parseConstant(const std::string& str) {
        double value = std::stod(str);

        return new Constant(value);
    }

    BaseFunction* Parser::parseFunction(const std::string& str) {
        std::stringstream ss;

        // extract function symbol
        auto it = str.begin();
        while (!(it == str.end() || *it == '(')) {
            ss << *it;

            it++;
        }

        const std::string& symbol = ss.str();
        const std::string& argument = getBracketContent(str, it);
        Expression* argumentExpr = parse(argument);

        if (symbol == "sin") {
            return new Sin(argumentExpr);
        }
        else if (symbol == "cos") {
            return new Cos(argumentExpr);
        }
        else if (symbol == "tan") {
            return new Tan(argumentExpr);
        }
        else if (symbol == "sinh") {
            return new Sinh(argumentExpr);
        }
        else if (symbol == "cosh") {
            return new Cosh(argumentExpr);
        }
        else if (symbol == "ln") {
            return new Ln(parse(argument));
        }

        throw new std::runtime_error("Function " + symbol + " is not defined");
    }

    std::string Parser::getBracketContent(const std::string& str, int begin) {
        auto it = str.begin() + begin;

        return getBracketContent(str, it);
    }

    std::string Parser::getBracketContent(const std::string& str, std::string::const_iterator it) {
        int bracketCounter = 0;

        std::stringstream content;
        while (!(it == str.end() || *it == ')' && bracketCounter == 0)) {
            char character = *it;

            switch (character) {
                case '(':
                    if (bracketCounter > 0) {
                        content << character;
                    }
                    bracketCounter++;
                    break;
                case ')':
                    bracketCounter--;
                    if (bracketCounter > 0) {
                        content << character;
                    }
                    break;
                default:
                    content << character;
                    break;
            }

            it++;
        }

        return content.str();
    }

    Expression* Parser::parse(const std::string& str) {
        return parseAddition(str);
    }
} // namespace cas::io
