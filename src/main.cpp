#include <iostream>

#include "math/operators/differential.hpp"
#include "io/parser.hpp"
#include "math/expressions/simplifier.hpp"

using namespace cas::math;

int main(int argCnt, char** args) {
    std::string function;

    while (true) {
        std::cout << "Enter a function f(x,y)=";
        std::cin >> function;

        Expression* expr = Parser::parse(function);

        Expression* differential = D(expr);

        std::cout << "df=" << differential->toString() << std::endl;
    }
}
