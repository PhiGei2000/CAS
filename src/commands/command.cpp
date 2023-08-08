#include "commands/command.hpp"

#include "commands/commandWrapper.hpp"

#include "io/engine.hpp"
#include "io/ioStream.hpp"
#include "io/parser.hpp"

#include <mathlib/mathlib.hpp>

namespace cas::commands {
    template<>
    cas::math::Expression* parseArg(Engine* engine, const std::string& argStr) {
        if (isNestedCommand(argStr)) {
            CommandResult result = executeNestedCommand(engine, argStr);

            return result.expr;
        }

        return cas::io::Parser::parse(argStr);
    }

    template<>
    cas::math::Variable* parseArg(Engine* engine, const std::string& argStr) {
        if (isNestedCommand(argStr)) {
            CommandResult result = executeNestedCommand(engine, argStr);

            return reinterpret_cast<Variable*>(result.expr);
        }

        return new Variable(argStr);
    }

    bool isNestedCommand(const std::string& arg) {
        return arg.contains('[');
    }

    CommandResult executeNestedCommand(Engine* engine, const std::string& command) {
        io::IOStream::Command parsed = io::IOStream::parseCommand(command);

        CommandWrapper wrapper = engine->getCommand(parsed.alias);
        CommandResult result = wrapper.executeCommand(engine, parsed.args);

        if (result.type == CommandResult::ResultTypes::EXPRESSION) {
            return CommandResult(result.expr->copy());
        }

        return result;
    }
} // namespace cas::commands