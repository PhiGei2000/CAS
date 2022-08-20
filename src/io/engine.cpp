#include "io/engine.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace cas {
    
    void Engine::addCommand(const std::string& alias, CommandDelegate delegate) {
        commands[alias] = delegate;
    }

    void Engine::run() const {
        std::string input;

        while (true) {
            std::cout << ">";

            std::cin >> input;

            if (input == "stop") {
                return;
            }

            try {
                const CommandArgs& data = parseCommand(input);

                try {
                    const CommandDelegate& delegate = commands.at(data.alias);
                    std::cout << delegate(data) << std::endl;
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