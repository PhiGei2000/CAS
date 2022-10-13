#pragma once
#include <functional>
#include <string>
#include <map>
#include <unordered_map>

#include "commands/command.hpp"
#include "math/expressions/terms/variable.hpp"

using namespace cas::commands;

namespace cas {
    class Engine {
      private:
        static constexpr unsigned int bufferSize = 512;

        std::unordered_map<std::string, basic_command*> commands;
        std::map<cas::math::VariableSymbol, Expression*> vars;

        void setupCommands();

      public:
        Engine();

        template<CommandType TCommand>
        void addCommand(const std::string& alias);

        void run() const;
    };
} // namespace cas