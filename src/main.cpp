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

        Expression* derivativeX = D(expr, Variable('x'));
        Expression* derivativeY = D(expr, Variable('y'));
        Expression* simplifiedX = derivativeX->simplify();
        Expression* simplifiedY = derivativeY->simplify();

        std::cout << "df/dx=" << simplifiedX->toString() << std::endl;
        std::cout << "df/dy=" << simplifiedY->toString() << std::endl;
    }
}
