#include "io/engine.hpp"

#include "commands/differentialCalculus.hpp"
#include "commands/termManipulation.hpp"
#include "commands/termMatching.hpp"

#include "io/ioStream.hpp"
#include <mathlib/mathlib.hpp>

#include <iomanip>
#include <sstream>

namespace cas {
    void Engine::setupCommands() {
#pragma region Callbacks
        CommandCallback<std::string> printStr = [&](std::string str) {
            io::IOStream::writeLine(str);
        };

        CommandCallback<math::Expression*> printExpression = [&](math::Expression* expr) {
            // Expression* simplified = expr->simplify();
            // io::IOStream::writeLine(simplified->toString());
            io::IOStream::writeLine(expr->toString());

            delete expr;
            // delete simplified;
        };

        CommandCallback<math::ExpressionMatch> printExpressionMatch = [&](math::ExpressionMatch match) {
            std::stringstream ss;

            const char separator = ' ';
            const int symbolWidth = 10;

            ss << std::left << std::setw(symbolWidth) << std::setfill(separator) << "Variable"
               << " | "
               << "Value";

            for (const auto& [var, expr] : match.variables) {
                ss << std::endl;
                ss << std::left << std::setw(symbolWidth) << std::setfill(separator) << var << " | ";
                ss << expr->toString();
            }

            io::IOStream::writeLine(ss.str());
        };

        CommandCallback<std::vector<math::ExpressionMatch>> printExpressionMatches = [&](std::vector<math::ExpressionMatch> matches) {
            std::stringstream ss;
            ss << "Found " << matches.size() << " matches" << std::endl;

            const char separator = ' ';
            const int symbolWidth = 10;

            for (const auto match : matches) {
                ss << "Match: " << *match.node << std::endl;
                ss << std::left << std::setw(symbolWidth) << std::setfill(separator) << "Variable"
                   << " | "
                   << "Value";

                for (const auto& [var, expr] : match.variables) {
                    ss << std::endl;
                    ss << std::left << std::setw(symbolWidth) << std::setfill(separator) << var << " | ";
                    ss << expr->toString();
                }
                ss << std::endl;
            }
            io::IOStream::writeLine(ss.str());
        };
#pragma endregion

        Command<std::string> exitCommand = Command<std::string>([](Engine* engine) {
            engine->running = false;

            return "shutting down!";
        });
        addCommand("exit", exitCommand, printStr);

        // TODO: Add short form x=expr; == set[x,expr];
        Command<math::Expression*, math::Variable*, math::Expression*> setCommand = Command<math::Expression*, math::Variable*, math::Expression*>(
            [](Engine* engine, math::Variable* var, math::Expression* expr) {
                engine->vars[var->getSymbol()] = expr;

                return expr;
            });
        addCommand("set", setCommand);

        Command<std::string> listVarsCommand = Command<std::string>(
            [](Engine* engine) {
                std::stringstream ss;

                const char separator = ' ';
                const int symbolWidth = 10;

                ss << std::left << std::setw(symbolWidth) << std::setfill(separator) << "Variable"
                   << " | "
                   << "Value";

                for (const auto& [symbol, expr] : engine->vars) {
                    ss << std::endl;
                    ss << std::left << std::setw(symbolWidth) << std::setfill(separator) << symbol << " | ";
                    ss << expr->toString();
                }

                return ss.str();
            });
        addCommand("listVars", listVarsCommand, printStr);

        addCommand("D", commands::differentiate, printExpression);
        addCommand("Df", commands::differential, printExpression);
        addCommand("simplify", commands::simplify, printExpression);
        addCommand("match", commands::matchCommand, printExpressionMatch);
        addCommand("matchRecurse", commands::matchRecurseCommand, printExpressionMatch);
        addCommand("matchAll", commands::matchAllCommand, printExpressionMatches);
        addCommand("substitute", commands::substituteCommand, printExpression);
    }
} // namespace cas
