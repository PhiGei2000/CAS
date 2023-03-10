#pragma once
#include <functional>
#include <string>

#include "utility.hpp"

namespace cas::commands {
    template<typename T>
    T parseArg(const std::string& arg);

    template<typename TRes, typename... TArgs>
    struct Command {
      protected:
        std::function<TRes*(TArgs*...)> callback;

      public:
        inline TRes* execute(const std::string& argStr) const {
            const std::vector<std::string>& argV = cas::splitString(argStr, ",");

            std::index_sequence<sizeof...(TArgs)> indices = std::make_index_sequence<sizeof...(TArgs)>();
            return callback(parseArg<TArgs>(argV[indices])...);
        }
    };

    template<typename TRes, typename... TArgs>
    using CommandCallback = std::function<void(TRes*)>;

    template<typename TRes, typename... TArgs>
    constexpr CommandCallback<TRes> DefaultCallback = [](TRes* result) {};

    struct CommandWrapper {
      private:
        std::function<void(const std::string&)> functional;

      public:
        template<typename TRes, typename... TArgs>
        CommandWrapper(Command<TRes, TArgs...> command, CommandCallback<TRes> callback = DefaultCallback<TRes>) {
            functional = [&](const std::string& argStr) {
                TRes* result = command.execute(argStr);
                callback(result);

                delete result;
            };
        }

        void executeCommand(const std::string& argStr) const {
            functional(argStr);
        }
    };
} // namespace cas::commands
