#pragma once

#include "command.hpp"

#include "math/expressions/expressions.hpp"

using namespace cas::math;

namespace cas::commands {  
    class D : public Command<Expression, Variable> {
      protected:
        virtual Expression* operator()(Expression* input, Variable* var) const override;
    };

    class Df : public Command<Expression> {
      protected:
        virtual Expression* operator()(Expression* input) const override;
    };      
} // namespace cas::commands