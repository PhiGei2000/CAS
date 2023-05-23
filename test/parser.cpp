#include <iostream>
#include <string>
#include <unordered_map>

#include "io/parser.hpp"
#include <mathlib/mathlib.hpp>

using namespace cas::math;
using namespace cas::io;

std::unordered_map<std::string, Expression*> expressions = {
    std::make_pair("x", new Variable("x")),
    std::make_pair("x-2+x", new Addition(new Variable("x"), new Addition(new Number(-2), new Variable("x")))),
    std::make_pair("x-2", new Addition(new Variable("x"), new Number(-2))),
    std::make_pair("sin(x-2)", new Sin(new Addition(new Variable("x"), new Number(-2))))
};

int main(int argC, char** argV) {
    bool missmatch = false;

    for (const auto& [str, exprExpected] : expressions) {
        Expression* expr = Parser::parse(str);

        if (!matchExpressions(expr, exprExpected)) {
            std::cout << "expected: " << exprExpected->toString() << " got: " << expr->toString() << std::endl;
            missmatch = true;
        }

        delete expr;
    }

    return missmatch;
}