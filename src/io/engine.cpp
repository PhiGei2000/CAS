#include "io/engine.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "commands/differentialCalculus.hpp"

namespace cas {
    void Engine::setupCommands() {
        this->addCommand<commands::D>("D");
        this->addCommand<commands::Df>("Df");
    }

    Engine::Engine() {
        setupCommands();
    }


    template<CommandType TCommand>
    void Engine::addCommand(const std::string& alias) {
        commands[alias] = new TCommand();
    }

    void Engine::run() const {
        char buffer[bufferSize];

        while (true) {
            std::cout << ">";

            std::cin.getline(buffer, bufferSize);

            std::string input = buffer;
            if (input == "exit") {
                return;
            }

            try {
                const CommandArgs& data = parseCommand(input);

                try {
                    const basic_command* command = commands.at(data.alias);

                    Expression* result = command->execute(data);
                    Expression* simplified = result->simplify();
                    std::cout << simplified->toString() << std::endl;

                    delete result;
                    delete simplified;
                }
                catch (const std::out_of_range&) {
                    std::cout << "Command \"" << data.alias << "\" not found" << std::endl;
                }
            }
            catch (const std::runtime_error& e) {
                std::cout << e.what() << std::endl;
                continue;
            }
        }
    }
} // namespace cas