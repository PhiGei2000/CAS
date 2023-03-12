#include "io/engine.hpp"

#include "io/ioStream.hpp"
#include <mathlib/mathlib.hpp>

namespace cas {
    void Engine::setupCommands() {
        CommandCallback<std::string> printStr = [&](std::string str) {
            io::IOStream::writeLine(str);
        };

        Command<std::string> exitCommand = Command<std::string>([](Engine* engine) {
            engine->running = false;

            return "shutting down!";
        });

        Command<math::Expression*, math::Variable*, math::Expression*> setCommand = Command<math::Expression*, math::Variable*, math::Expression*>(
            [](Engine* engine, math::Variable* var, math::Expression* expr) {
                engine->vars[var->getSymbol()] = expr;

                return expr;
        });        

        addCommand("exit", exitCommand, printStr);
        addCommand("set", setCommand);
    }
} // namespace cas
