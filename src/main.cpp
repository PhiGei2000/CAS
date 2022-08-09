#include <iostream>

#include "math/differential.hpp"
#include "math/expressions/parser.hpp"
#include "math/expressions/simplifier.hpp"

using namespace cas::math;

int main(int argCnt, char** args) { 
    while (true) {
        std::cout << "Enter a function f(x,y)=";
        std::string function;
        std::cin >> function;

        Expression* expr = Parser::parse(function);

        Expression* differential = D(expr);

        std::cout << "df=" << differential->toString() << std::endl;
    }
}
