#pragma once
#include <functional>
#include <string>
#include <unordered_map>

#include "commands/command.hpp"

using namespace cas::commands;

namespace cas {
    class Engine {
      private:
        std::unordered_map<std::string, basic_command*> commands;

        void setupCommands();

      public:
        Engine();

        template<CommandType TCommand>        
        void addCommand(const std::string& alias);

        void run() const;
    };
} // namespace cas