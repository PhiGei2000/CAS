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
        addCommand("exit", exitCommand);

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
        addCommand("listVars", listVarsCommand);

        addCommand("D", commands::differentiate);
        addCommand("Df", commands::differential);
        addCommand("simplify", commands::simplify);
        addCommand("match", commands::matchCommand);
        addCommand("matchRecurse", commands::matchRecurseCommand);
        addCommand("matchAll", commands::matchAllCommand);
        addCommand("substitute", commands::substituteCommand);
    }
} // namespace cas
