#pragma once

#include "command.hpp"

#include "math/expressions/expressions.hpp"


using namespace cas::math;

namespace cas::commands {
    class D : public Command<Expression*, Variable*> {

        virtual Expression* operator()(Expression* input, Variable* var) const override;
    };

    class Df : public Command<Expression*> {
        virtual Expression* operator()(Expression* input);
    };

    // CommandDelegate D = [](const CommandArgs& args) {
    //     // parse arguments and simplify the input
    //     Expression* input = args.getArg<Expression*>(0);
    //     Expression* simplifiedInput = input->simplify();
    //     Variable* var = args.getArg<Variable*>(1);

    //     // execute the command and simplify the result
    //     Expression* result = cas::math::D(simplifiedInput, *var);
    //     Expression* simplifiedResult = result->simplify();

    //     // convert the result into a string
    //     const std::string& out = simplifiedResult->toString();
    //     // const std::string& out = result->toString();

    //     // Clean up memory
    //     delete var;
    //     delete input;
    //     delete simplifiedInput;
    //     delete result;
    //     delete simplifiedResult;

    //     // return result
    //     return out;
    // };

    // CommandDelegate Df = [](const CommandArgs& args) {
    //     Expression* function = args.getArg<Expression*>(0);
    //     Expression* simplified = function->simplify();

    //     Expression* differential = cas::math::D(function);
    //     Expression* simplifiedDifferential = differential->simplify();

    //     const std::string& out = simplifiedDifferential->toString();

    //     // clean up memory
    //     delete function;
    //     delete simplified;
    //     delete differential;
    //     delete simplifiedDifferential;

    //     return out;
    // };

    // CommandDelegate Matches = [](const CommandArgs& args) {
    //     Expression* expression = args.getArg<Expression*>(0);
    //     Expression* pattern = args.getArg<Expression*>(1);

    //     ExpressionMatcher matcher = ExpressionMatcher(pattern);
    //     bool match = matcher.matches(expression);

    //     return match ? "true" : "false";
    // };

    // CommandDelegate Match = [](const CommandArgs& args) {
    //     Expression* expression = args.getArg<Expression*>(0);
    //     Expression* pattern = args.getArg<Expression*>(1);

    //     ExpressionMatcher matcher = ExpressionMatcher(pattern);
    //     ExpressionMatch match = matcher.match(expression);

    //     std::stringstream ss;
    //     ss << "{ success: ";
    //     ss << (match.success ? "true" : "false");

    //     ss << ", variables: [";

    //     for (const auto [var, expr] : match.variables) {
    //         ss << var.getSymbol() << "=" << expr->toString() << ",";
    //     }

    //     ss << "]}";

    //     return ss.str();
    // };
} // namespace cas::commands