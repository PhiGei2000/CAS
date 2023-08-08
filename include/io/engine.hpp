#pragma once
#include <map>
#include <string>
#include <unordered_map>

#include "commands/commandWrapper.hpp"

#include <mathlib/mathlib.hpp>

using namespace cas::math;
using namespace cas::commands;

namespace cas {
    class Engine {
      protected:
        struct Callbacks {
            static Command<std::string, std::string> printStringCallback;
            static Command<std::string, Expression*> printExpressionCallback;
            static Command<std::string, std::vector<ExpressionMatch>> printExpressionMatchCallback;
        };

        std::unordered_map<std::string, CommandWrapper> commands;
        std::unordered_map<cas::math::VariableSymbol, cas::math::Expression*> vars;
        bool running = false;
        Expression* ans = nullptr;

        void setupCommands();

        void handleVariableInput(const std::string& input);

        void handleCommandResult(CommandResult& result);

        friend struct cas::commands::CommandWrapper;

      public:
        Engine();

        template<typename TRes, typename... TArgs>
        inline void addCommand(const std::string& alias, const Command<TRes, TArgs...>& command) {
            commands[alias] = CommandWrapper(command);
        }

        CommandWrapper getCommand(const std::string& alias) const;

        void run();
    };
} // namespace cas