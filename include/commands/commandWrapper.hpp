#pragma once
#include "command.hpp"
#include "commandCallback.hpp"

#include <mathlib/mathlib.hpp>

#include <iostream>

namespace cas {
    class Engine;
}

namespace cas::commands {
    struct CommandWrapper {
      protected:
        std::function<void(Engine*, const std::vector<std::string>&)> functional;

        static void saveAns(Engine* engine, cas::math::Expression* result);

      public:
        inline CommandWrapper() {
            functional = [](Engine* engine, const std::vector<std::string>& argV) {};
        }

        template<typename TRes, typename... TArgs>
        inline CommandWrapper(const Command<TRes, TArgs...>& command, CommandCallback<TRes> callback = DefaultCallback<TRes>) {
            functional = [command, callback](Engine* engine, const std::vector<std::string>& argV) {
                TRes result = command.execute(engine, argV);

                callback(result);
            };
        }

        template<typename... TArgs>
        inline CommandWrapper(const Command<cas::math::Expression*, TArgs...>& command, CommandCallback<cas::math::Expression*> callback = DefaultCallback<cas::math::Expression*>) {
            functional = [command, callback](Engine* engine, const std::vector<std::string>& argV) {
                cas::math::Expression* expr = command.execute(engine, argV);

                callback(expr);
                saveAns(engine, expr);
            };
        }

        inline void executeCommand(Engine* engine, const std::vector<std::string>& argV) const {
            functional(engine, argV);
        }
    };
} // namespace cas::commands