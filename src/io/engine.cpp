#include "io/engine.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace cas {
    CommandData Engine::parseCommand(const std::string& str) {
        int argumentsStart = str.find('[');
        int argumentsEnd = str.find_last_of(']');

        if (argumentsStart == std::string::npos || argumentsEnd == std::string::npos) {
            throw std::runtime_error("No arguments given");
        }

        std::string alias = str.substr(0, argumentsStart);
        std::string argumentsString = str.substr(argumentsStart + 1, argumentsEnd - argumentsStart - 1);

        std::vector<std::string> arguments;
        auto it = argumentsString.begin();

        do {
            std::stringstream ss;

            while (!(it == argumentsString.end() || *it == ',')) {
                ss << *it;
                it++;
            }

            if (it != argumentsString.end())
                it++;

            arguments.push_back(ss.str());
        } while (it != argumentsString.end());

        return CommandData{alias, arguments};
    }

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
                const CommandData& data = parseCommand(input);

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