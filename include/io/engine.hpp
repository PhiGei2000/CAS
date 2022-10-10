#pragma once
#include <functional>
#include <string>
#include <unordered_map>

#include "commands/command.hpp"

using namespace cas::commands;

namespace cas {

    class Engine {
      private:
        std::unordered_map<std::string, basic_command> commands;

      public:
        template<typename... TArgs, CommandType<TArgs...> TCommand>
        void addCommand(const std::string& alias, TCommand command);

        void run() const;
    };
} // namespace cas