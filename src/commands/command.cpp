#include "commands/command.hpp"

#include "expressions/expressions.hpp"

using namespace cas::math;

namespace cas::commands {
    template<>
    Expression* Command<Expression>::execute(const CommandArgs& args) const {        
        return this->operator()(args.getArg<Expression*>(0));
    }

    template<>
    Expression* Command<Expression, Variable>::execute(const CommandArgs& args) const {
        return this->operator()(args.getArg<Expression*>(0), args.getArg<Variable*>(1));
    }
} // namespace cas::commands