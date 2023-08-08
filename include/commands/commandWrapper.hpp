#pragma once
#include "command.hpp"
#include "commandResult.hpp"

#include <mathlib/mathlib.hpp>

#include <iostream>

namespace cas {
    class Engine;
}

namespace cas::commands {
    struct CommandWrapper {
      protected:
        std::function<CommandResult(Engine*, const std::vector<std::string>&)> functional;

        static void saveAns(Engine* engine, cas::math::Expression* result);

      public:
        inline CommandWrapper() {
            functional = [](Engine* engine, const std::vector<std::string>& argV) {
                return CommandResult(std::string(""));
            };
        }

        template<CommandResultType TRes, typename... TArgs>
        inline CommandWrapper(const Command<TRes, TArgs...>& command) {
            functional = [command](Engine* engine, const std::vector<std::string>& argV) {
                TRes result = command.execute(engine, argV);

                return CommandResult(result);
            };
        }

        template<typename... TArgs>
        inline CommandWrapper(const Command<cas::math::Expression*, TArgs...>& command) {
            functional = [command](Engine* engine, const std::vector<std::string>& argV) {
                cas::math::Expression* expr = command.execute(engine, argV);

                saveAns(engine, expr);
                return CommandResult(expr);
            };
        }

        inline CommandResult executeCommand(Engine* engine, const std::vector<std::string>& argV) const {
            return functional(engine, argV);
        }
    };
} // namespace cas::commands