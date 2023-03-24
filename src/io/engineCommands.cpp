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

        Command<std::string> exitCommand = Command<std::string>([](Engine* engine) {
            engine->running = false;

            return "shutting down!";
        });
        addCommand("exit", exitCommand, Callbacks::printStringCallback);

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
        addCommand("listVars", listVarsCommand, Callbacks::printStringCallback);

        addCommand("D", commands::differentiate, Callbacks::printExpressionCallback);
        addCommand("Df", commands::differential, Callbacks::printExpressionCallback);
        addCommand("simplify", commands::simplify, Callbacks::printExpressionCallback);
        addCommand("match", commands::matchCommand, Callbacks::printExpressionMatchCallback);
        addCommand("matchRecurse", commands::matchRecurseCommand, Callbacks::printExpressionMatchCallback);
        addCommand("matchAll", commands::matchAllCommand, Callbacks::printExpressionMatchesCallback);
        addCommand("substitute", commands::substituteCommand, Callbacks::printExpressionCallback);
    }
} // namespace cas
