#pragma once

#include "variable.hpp"

namespace cas::math {
    struct Differential : public Variable {
        Differential(char variable);

        virtual Expression* copy() const override;

        virtual ExpressionType getType() const override;
        virtual std::string toString() const override;
    };
} // namespace cas::math
