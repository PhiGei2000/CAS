#pragma once

#include "engine.hpp"
#include "io/parser.hpp"
#include "math/expressions/expressions.hpp"
#include "math/operators/differential.hpp"

using namespace cas::math;
using namespace cas::io;

namespace cas::commands {
    CommandDelegate D = [](const CommandArgs& args) {
        // parse arguments and simplify the input
        Expression* input = args.getArg<Expression*>(0);
        Expression* simplifiedInput = input->simplify();
        Variable* var = args.getArg<Variable*>(1);

        // execute the command and simplify the result
        Expression* result = cas::math::D(simplifiedInput, *var);
        Expression* simplifiedResult = result->simplify();

        // convert the result into a string
        const std::string& out = simplifiedResult->toString();
        // const std::string& out = result->toString();

        // Clean up memory
        delete var;
        delete input;
        delete simplifiedInput;
        delete result;
        delete simplifiedResult;

        // return result
        return out;
    };

    CommandDelegate Df = [](const CommandArgs& args) {
        Expression* function = args.getArg<Expression*>(0);
        Expression* simplified = function->simplify();

        Expression* differential = cas::math::D(function);
        Expression* simplifiedDifferential = differential->simplify();

        const std::string& out = simplifiedDifferential->toString();

        // clean up memory
        delete function;
        delete simplified;
        delete differential;
        delete simplifiedDifferential;

        return out;
    };
} // namespace cas::commands