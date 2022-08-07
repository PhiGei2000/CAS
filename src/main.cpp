#include <iostream>

#include "math/differential.hpp"

using namespace cas::math;

int main(int argCnt, char** args) {
    Constant c1 = 5.0;
    Constant c2 = 10;
    Constant c3 = 2;
    Variable v1 = 'x';

    auto x2 = Exponentiation(v1, c3);
    auto sum = Addition(c1, x2);
    auto expr = Sin(sum);

    auto derivative = D(&expr, Variable('x'))->simplify();

    std::cout << "d/dx(" << expr.toString() << ")=" << derivative->toString() << std::endl;
}
