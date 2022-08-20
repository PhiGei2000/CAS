#pragma once

#include "engine.hpp"
#include "io/parser.hpp"
#include "math/expressions/expressions.hpp"
#include "math/operators/differential.hpp"

using namespace cas::math;
using namespace cas::io;

namespace cas {
    namespace commands {
        CommandDelegate D = [](const CommandArgs& args) {
            Expression* input = Parser::parse(args.arguments[0]);
            Expression* simplifiedInput = input->simplify();

            if (args.arguments[1].length() != 1) {
                throw new std::runtime_error("Required variable name");
            }

            Variable var = Variable(args.arguments[1].front());

            Expression* result = math::D(simplifiedInput, var);
            Expression* simplifiedResult = result->simplify();
           
            const std::string& out = result->toString() + "=" + simplifiedResult->toString();

            // TODO: Clean up memory
            delete input;
            delete simplifiedInput;
            delete result;
            delete simplifiedResult;

            return out;
        };
    }
} // namespace cas