#pragma once
#include <string>
#include <vector>
#include <stdexcept>

namespace cas::commands {
    struct CommandArgs {
        std::string alias;
        std::vector<std::string> arguments;

        template<typename T> 
        T getArg(int index) const;
    };
    
    CommandArgs parseCommand(const std::string& input);

    struct command_arg_exception : public std::runtime_error {
        std::string commandAlias;
        int argumentIndex;
                
        command_arg_exception(const std::string& commandAlias, int argIndex, const std::string& message);
    };
}

