#pragma once
#include "command.hpp"

#include <iostream>

namespace cas::commands {
    template<typename TRes, typename... TArgs>
    using CommandCallback = std::function<void(TRes)>;

    template<typename TRes, typename... TArgs>
    static CommandCallback<TRes> DefaultCallback = [](TRes result) {};

    struct CommandWrapper {
      private:
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

        inline void executeCommand(Engine* engine, const std::vector<std::string>& argV) const {
            functional(engine, argV);
        }
    };
} // namespace cas::commands