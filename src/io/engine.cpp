#include "io/engine.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace cas {

    template<typename... TArgs, CommandType<TArgs...> TCommand>
    void Engine::addCommand(const std::string& alias, TCommand command) {
        commands[alias] = command;
    }

    void Engine::run() const {
        std::string input;

        while (true) {
            std::cout << ">";

            std::cin >> input;

            if (input == "exit") {
                return;
            }

            try {
                const CommandArgs& data = parseCommand(input);

                try {
                    const basic_command& command = commands.at(data.alias);
                    std::cout << command.execute(data) << std::endl;
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