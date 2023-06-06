#pragma once

#include "functions.hpp"
#include "terms/addition.hpp"
#include "terms/number.hpp"
#include "terms/differential.hpp"
#include "terms/exponentiation.hpp"
#include "terms/multiplication.hpp"
#include "terms/variable.hpp"

#include <concepts>

namespace cas {
    template<typename T>
    concept ExpressionType = std::derived_from<T, math::Expression>;

    template<typename T>
    concept NumericType = std::is_floating_point_v<T> || std::is_integral_v<T>;

    template<typename T>
    concept VariableSymbolType = std::is_same_v<math::VariableSymbol, T>;

    template<typename T>
    concept MathType = ExpressionType<T> || std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_same_v<char, T>;

    template<NumericType T>
    math::Expression* toExpression(T expr) {
        return new math::Number(expr);
    }

    template<VariableSymbolType T>
    math::Expression* toExpression(T expr) {
        return new math::Variable(expr);
    }

    template<ExpressionType T>
    math::Expression* toExpression(T* expr) {
        return expr;
    }
} // namespace cas
