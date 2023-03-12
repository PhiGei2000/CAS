#include "io/engine.hpp"

#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>

#include "io/ioStream.hpp"

namespace cas {
    Engine::Engine() {
        setupCommands();
    }

    void Engine::run() {
        running = true;

        while (running) {
            io::IOStream::Command command = io::IOStream::readCommand();
            // if (command.alias == "exit") {
            //     running = false;
            //     continue;
            // }

            try {
                commands.at(command.alias).executeCommand(this, command.args);
            }
            catch (const std::runtime_error& e) {
                std::cout << e.what() << std::endl;
                continue;
            }
            catch (const std::out_of_range& e) {
                std::cout << "Command \"" << command.alias << "\" not found!" << std::endl;
                continue;                
            }
        }
    }
} // namespace cas