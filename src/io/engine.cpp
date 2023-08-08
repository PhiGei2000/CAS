#include "io/engine.hpp"

#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>

#include "io/ioStream.hpp"
#include "io/parser.hpp"

namespace cas {
    Engine::Engine() {
        setupCommands();
    }

    CommandWrapper Engine::getCommand(const std::string& alias) const {
        return commands.at(alias);
    }

    void Engine::run() {
        running = true;

        Command<Expression*, Variable*, Expression*> setVariableCommand = Command<Expression*, Variable*, Expression*>(
            [](cas::Engine* engine, Variable* var, Expression* expr) {
                // No need of this part. The expression should be stored in the ans pointer. So it gets deleted automatically
                // if (engine->vars.contains(symbol)) {
                //    delete engine->vars[symbol];
                // }
                VariableSymbol symbol = var->getSymbol();

                engine->vars[symbol] = expr->copy();
                return engine->vars[symbol];
            });

        Command<Expression*, Variable*> getVariableCommand = Command<Expression*, Variable*>(
            [](Engine* engine, Variable* var) {
                return engine->vars.at(var->getSymbol())->copy();
            });

        Command<Expression*> ansCommand = Command<Expression*>(
            [](Engine* engine) {
                return engine->ans->copy();
            });

        addCommand("set", setVariableCommand);
        addCommand("get", getVariableCommand);
        addCommand("ans", ansCommand);

        while (running) {
            io::IOStream::Command command = io::IOStream::readCommand();

            try {
                CommandResult result = commands.at(command.alias).executeCommand(this, command.args);
                handleCommandResult(result);
            }
            catch (const std::runtime_error& e) {
                std::cout << e.what() << std::endl;
                continue;
            }
            catch (const std::out_of_range& e) {
                const std::string& input = command.alias;
                if (input.contains('=')) {
                    size_t splitPosition = input.find('=');

                    const VariableSymbol symbol = input.substr(0, splitPosition);
                    const std::string& exprStr = input.substr(splitPosition + 1);

                    commands.at("set").executeCommand(this, {symbol, exprStr});
                    continue;
                }
                else if (vars.contains(input)) {
                    commands["get"].executeCommand(this, {input});
                    continue;
                }

                std::cout << "Command \"" << command.alias << "\" not found!" << std::endl;
                continue;
            }
        }
    }
} // namespace cas