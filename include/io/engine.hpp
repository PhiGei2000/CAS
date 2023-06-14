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
            static CommandCallback<std::string> printStringCallback;
            static CommandCallback<Expression*> printExpressionCallback;
            static CommandCallback<ExpressionMatch> printExpressionMatchCallback;
            static CommandCallback<std::vector<ExpressionMatch>> printExpressionMatchesCallback;
        };

        std::unordered_map<std::string, CommandWrapper> commands;
        std::unordered_map<cas::math::VariableSymbol, cas::math::Expression*> vars;
        bool running = false;
        Expression* ans = nullptr;

        void setupCommands();

        void handleVariableInput(const std::string& input);

        friend struct cas::commands::CommandWrapper;

      public:
        Engine();

        template<typename TRes, typename... TArgs>
        inline void addCommand(const std::string& alias, const Command<TRes, TArgs...>& command, CommandCallback<TRes>& callback = DefaultCallback<TRes>) {
            commands[alias] = CommandWrapper(command, callback);
        }

        void run();
    };
} // namespace cas