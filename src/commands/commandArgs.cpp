#include "commands/commandArgs.hpp"

#include "io/parser.hpp"
#include "expressions/expressions.hpp"
#include "utility.hpp"

#include <sstream>
#include <stdexcept>

namespace cas::commands {
    template<>
    cas::math::Expression* CommandArgs::getArg<cas::math::Expression*>(int index) const {
        std::string arg = arguments.at(index);

        return cas::io::Parser::parse(removeWhiteSpaces(arg));
    }

    template<>
    cas::math::Variable* CommandArgs::getArg<cas::math::Variable*>(int index) const {
        std::string arg = arguments.at(index);

        removeWhiteSpaces(arg);
        if (arg.size() != 1) {
            throw command_arg_exception(alias, index, "Variable required");
        }

        return new Variable(arg.front());
    }

    CommandArgs parseCommand(const std::string& input) {
        int argumentsStart = input.find('[');
        int argumentsEnd = input.find_last_of(']');

        if (argumentsStart == std::string::npos || argumentsEnd == std::string::npos) {
            throw std::runtime_error("No arguments given");
        }

        std::string alias = input.substr(0, argumentsStart);
        std::string argumentsString = input.substr(argumentsStart + 1, argumentsEnd - argumentsStart - 1);

        std::vector<std::string> arguments;
        auto it = argumentsString.begin();

        do {
            std::stringstream ss;

            while (!(it == argumentsString.end() || *it == ',')) {
                ss << *it;
                it++;
            }

            if (it != argumentsString.end())
                it++;

            arguments.push_back(ss.str());
        } while (it != argumentsString.end());

        return CommandArgs{alias, arguments};
    }

    command_arg_exception::command_arg_exception(const std::string& commandAlias, int argIndex, const std::string& message)
        : std::runtime_error(message), commandAlias(commandAlias), argumentIndex(argIndex) {
    }
} // namespace cas::commands