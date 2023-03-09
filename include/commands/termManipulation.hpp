#pragma once

#include "command.hpp"

#include "expressions/expressions.hpp"

using namespace cas::math;

namespace cas::commands {
    class Simplify : public Command<Expression> {
      protected:
        virtual Expression* operator()(Expression* input) const override;
    };
} // namespace cas::commands