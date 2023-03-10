#include "io/engine.hpp"

#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>

namespace cas {
    Engine::Engine() {
        setupCommands();
    }

    void Engine::run() const {
        char buffer[bufferSize];        

        while (true) {
            std::cout << ">";

            std::cin.getline(buffer, bufferSize);

            std::string input = removeWhiteSpaces(input);
            if (input == "exit") {
                return;
            }

            try {
                size_t commandArgsBegin = input.find(commandArgBrackets[0]);
                size_t commandArgsEnd = input.find_last_of(commandArgBrackets[1]) - 1;

                const std::string& alias = input.substr(0, commandArgsBegin);
                const std::string& argStr = input.substr(commandArgsBegin + 1, commandArgsEnd - commandArgsBegin);

                commands.at(alias).executeCommand(argStr);
            }
            catch (const std::runtime_error& e) {
                std::cout << e.what() << std::endl;
                continue;
            }
        }
    }
} // namespace cas