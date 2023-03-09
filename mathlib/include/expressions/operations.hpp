#pragma once
#include "expressions.hpp"

namespace cas::math {
    template<typename TLeft, typename TRight>
    inline Expression* add(TLeft left, TRight right) {
        return new Addition(toExpression(left), toExpression(right));
    }

    template<typename TLeft, typename TRight>
    inline Expression* multiply(TLeft left, TRight right) {
        return new Multiplication(toExpression(left), toExpression(right));
    }

    template<typename TLeft, typename TRight>
    Expression* power(TLeft left, TRight right) {
        return new Exponentiation(toExpression(left), toExpression(right));
    }

    template<typename TLeft, typename TRight>
    inline Expression* subtract(TLeft left, TRight right) {
        return add(left, multiply(-1, right));
    }

    template<typename TLeft, typename TRight>
    Expression* divide(TLeft left, TRight right) {
        return multiply(left, power(right, -1));
    }

    template<typename T>
    Expression* sqrt(T expression) {
        return power(expression, 0.5);
    }
} // namespace cas::math