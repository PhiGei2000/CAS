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

    void Engine::run() {
        running = true;

        Command<Expression*, VariableSymbol, Expression*> setVariableCommand = Command<Expression*, VariableSymbol, Expression*>(
            [](cas::Engine* engine, VariableSymbol symbol, Expression* expr) {
                if (engine->vars.contains(symbol)) {
                    delete engine->vars[symbol];
                }

                engine->vars[symbol] = expr;
                return expr->copy();
            });
        
        Command<Expression*, VariableSymbol> getVariableCommand = Command<Expression*, VariableSymbol>(
            [](Engine* engine, VariableSymbol symbol) {
                return engine->vars.at(symbol)->copy();
            });

        Command<Expression*> ansCommand = Command<Expression*>(
            [](Engine* engine) {
                return engine->ans->copy();
            }
        );

        commands["set"] = StoreableCommandWrapper(setVariableCommand, Callbacks::printExpressionCallback);
        commands["get"] = StoreableCommandWrapper(getVariableCommand, Callbacks::printExpressionCallback);
        commands["ans"] = StoreableCommandWrapper(ansCommand, Callbacks::printExpressionCallback);

        while (running) {
            io::IOStream::Command command = io::IOStream::readCommand();

            try {
                commands.at(command.alias).executeCommand(this, command.args);
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