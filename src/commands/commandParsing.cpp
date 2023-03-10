#include "commands/command.hpp"

#include "io/parser.hpp"

#include <mathlib/mathlib.hpp>

namespace cas::commands {
    template<>
    cas::math::Expression* parseArg(const std::string& argStr) {
        return cas::io::Parser::parse(argStr);
    }

    template<>
    cas::math::Variable* parseArg(const std::string& argStr) {
        return new Variable(argStr);
    }
}