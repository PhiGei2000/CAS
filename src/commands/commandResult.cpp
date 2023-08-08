#include "commands/commandResult.hpp"

namespace cas::commands {
    template<>
    CommandResult::CommandResult(std::string text)
        : text(text), type(ResultTypes::STRING) {
    }

    template<>
    CommandResult::CommandResult(math::Expression* expr)
        : expr(expr), type(ResultTypes::EXPRESSION) {
    }

    template<>
    CommandResult::CommandResult(math::ExpressionMatch match)
        : matches({match}), type(ResultTypes::MATCH_LIST) {
    }

    template<>
    CommandResult::CommandResult(std::vector<math::ExpressionMatch> matches)
        : matches(matches), type(ResultTypes::MATCH_LIST) {
    }
} // namespace cas::commands