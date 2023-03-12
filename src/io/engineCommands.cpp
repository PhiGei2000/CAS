#include "io/engine.hpp"

#include "io/ioStream.hpp"
#include <mathlib/mathlib.hpp>

#include <iomanip>
#include <sstream>

namespace cas {
    void Engine::setupCommands() {
        CommandCallback<std::string> printStr = [&](std::string str) {
            io::IOStream::writeLine(str);
        };

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
    }
} // namespace cas
