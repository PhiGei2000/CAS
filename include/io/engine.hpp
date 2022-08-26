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
      template<typename TOut, typename... TArgs>
        void addCommand(const std::string& alias, Command<TOut, TArgs...> delegate);

        void run() const;
    };
} // namespace cas