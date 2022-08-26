#include "commands/command.hpp"

#include "math/expressions/terms/expression.hpp"

namespace cas::commands {
    template<typename...TArgs>
    cas::math::Expression* Command<TArgs...>::execute(const CommandArgs& args) const {
        return this->operator()(getArgs(args));
    }
} // namespace cas::commands
