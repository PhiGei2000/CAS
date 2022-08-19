#pragma once

#include "engine.hpp"
#include "io/parser.hpp"
#include "math/expressions/expressions.hpp"
#include "math/operators/differential.hpp"

using namespace cas::math;

namespace cas {
    namespace commands {
        CommandDelegate D = [](const CommandData& data) {
            Expression* expr = Parser::parse(data.arguments[0]);

            if (data.arguments[1].length() != 1) {
                throw new std::runtime_error("Required variable name");
            }

            Variable var = Variable(data.arguments[1].front());

            Expression* result = math::D(expr->simplify(), var)->simplify();

            const std::string& out = result->simplify()->toString();

            // TODO: Clean up memory

            return out;
        };
    }
} // namespace cas