#pragma once
#include "command.hpp"
#include "commandCallback.hpp"

#include <mathlib/mathlib.hpp>

#include <iostream>

namespace cas::commands {
    struct CommandWrapper {
      protected:
        std::function<void(Engine*, const std::vector<std::string>&)> functional;

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
                delete expr;
            };
        }

        inline void executeCommand(Engine* engine, const std::vector<std::string>& argV) const {
            functional(engine, argV);
        }
    };

    struct StoreableCommandWrapper : public CommandWrapper {
        template<typename... TArgs>
        inline StoreableCommandWrapper(const Command<cas::math::Expression*, TArgs...>& command, CommandCallback<math::Expression*> callback = DefaultCallback<math::Expression*>, bool storeResult = true) {
            functional = [command, callback, storeResult](Engine* engine, const std::vector<std::string>& argV) {
                math::Expression* result = command.execute(engine, argV);
                if (storeResult) {
                    storeVariable(engine, result);
                }

                callback(result);
            };
        }

      protected:
        static void storeVariable(Engine* engine, math::Expression* expr);
    };
} // namespace cas::commands