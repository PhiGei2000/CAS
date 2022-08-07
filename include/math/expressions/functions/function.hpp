#pragma once

#include "../expression.hpp"

namespace cas::math {
    struct Function : public Expression {
      public:
        virtual std::string getName() const = 0;
        virtual ExpressionType getType() const {
            return ExpressionType::Function;
        }
    };
} // namespace cas::math