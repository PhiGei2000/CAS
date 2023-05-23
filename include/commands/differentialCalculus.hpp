#pragma once

#include "command.hpp"

#include <mathlib/mathlib.hpp>

using namespace cas::math;

namespace cas {
    class Engine;

    namespace commands {
        static const Command<Expression*, Expression*, Variable*> differentiate = Command<Expression*, Expression*, Variable*>(
            [](Engine* engine, Expression* expr, Variable* var) {
                return expr->differentiate(var);
            });

        static const Command<Expression*, Expression*> differential = Command<Expression*, Expression*>(
            [](Engine* engine, Expression* expr) {
                std::set<Variable> vars = expr->getVariables();
                Expression* result = new Number(0);

                if (vars.size() > 0) {
                    delete result;

                    auto it = vars.begin();
                    result = new Multiplication(expr->differentiate(&(*it)), new Differential(it->getSymbol()));
                    it++;

                    while (it != vars.end()) {
                        Expression* d = new Multiplication(expr->differentiate(&(*it)), new Differential(it->getSymbol()));
                        Expression* tmp = new Addition(result, d);

                        result = tmp;
                        it++;
                    }
                }

                return result;
            });
    } // namespace commands
} // namespace cas