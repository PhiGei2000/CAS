#pragma once
#include <concepts>

#include "commandArgs.hpp"
#include "math/expressions/expressions.hpp"

using namespace cas::math;

namespace cas::commands {
    class basic_command {
      public:
        virtual cas::math::Expression* execute(const CommandArgs& args) const = 0;
    };

    template<ExpressionType... TArgs>
    class Command : public basic_command {      
      protected:
        virtual cas::math::Expression* operator()(TArgs*... args) const = 0;

      public:
        cas::math::Expression* execute(const CommandArgs& args) const override;
    };

    template<typename T>
    concept CommandType = std::derived_from<T, basic_command>;
} // namespace cas::commands
