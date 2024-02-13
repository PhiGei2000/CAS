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

    template<CommandResultType TRes, typename T>
    inline static bool hasReferenceTo(TRes result, T* pointer) {
        return false;
    }

    template<>
    inline bool hasReferenceTo(math::ExpressionMatch result, math::Expression* pointer) {
        if (result.matchedNode == nullptr) {
            return false;
        }

        return result.matchedNode->getRoot() == pointer->getRoot();
    }

    template<>
    inline bool hasReferenceTo(std::vector<math::ExpressionMatch> result, math::Expression* pointer) {
        for (const auto match : result) {
            if (hasReferenceTo(match, pointer)) {
                return true;
            }
        }

        return false;
    }
} // namespace cas::commands