#pragma once
#include <functional>
#include <map>
#include <string>
#include <unordered_map>

#include "commands/command.hpp"
#include <mathlib/mathlib.hpp>

using namespace cas::commands;

namespace cas {
    class Engine {
      private:
        static constexpr unsigned int bufferSize = 512;
        static constexpr char commandArgBrackets[2] = {'[', ']'};

        std::unordered_map<std::string, CommandWrapper> commands;
        std::unordered_map<cas::math::VariableSymbol, cas::math::Expression*> vars;

        void setupCommands();

      public:
        Engine();

        template<typename TRes, typename... TArgs>
        inline void addCommand(const std::string& alias, Command<TRes, TArgs...>& command, CommandCallback<TRes>& callback = DefaultCallback<TRes>) {
            commands[alias] = CommandWrapper(command, callback);
        }

        void run() const;
    };
} // namespace cas