#pragma once

#include "../terms/expression.hpp"

namespace cas::math {
    struct Function : public Expression {
      public:
        virtual std::string getName() const = 0;
        virtual ExpressionTypes getType() const {
            return ExpressionTypes::Function;
        }
    };
} // namespace cas::math