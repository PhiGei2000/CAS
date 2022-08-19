#pragma once
#include <functional>
#include <string>
#include <unordered_map>

// #include "commandInterpreter.hpp"

namespace cas {
    struct CommandData {
        std::string alias;
        std::vector<std::string> arguments;
    };

    typedef std::function<std::string(const CommandData&)> CommandDelegate;

    class Engine {
      private:
        // CommandInterpreter interpreter;
        std::unordered_map<std::string, CommandDelegate> commands;

        static CommandData parseCommand(const std::string& input);
      public:
        void
        addCommand(const std::string& alias, CommandDelegate delegate);

        void run() const;
    };
} // namespace cas