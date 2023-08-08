#pragma once
#include <mathlib/mathlib.hpp>

#include <string>
#include <type_traits>
#include <vector>

namespace cas::commands {
    template<typename T>
    concept CommandResultType = std::is_same_v<T, std::string> || ExpressionType<std::remove_pointer_t<T>> || std::is_same_v<T, math::ExpressionMatch> || std::is_same_v<T, std::vector<cas::math::ExpressionMatch>>;

    struct CommandResult {
      public:
        enum ResultTypes {
            STRING,
            EXPRESSION,
            MATCH_LIST
        } type;

        template<CommandResultType T>
        CommandResult(T data);

        std::string text = "";
        math::Expression* expr = nullptr;
        std::vector<math::ExpressionMatch> matches;
    };
} // namespace cas::commands