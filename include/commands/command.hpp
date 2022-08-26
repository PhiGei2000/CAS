#pragma once

#include "commandArgs.hpp"

namespace cas::math {
    struct Expression;
}

namespace cas::commands {
    class basic_command {
        virtual cas::math::Expression* execute(const CommandArgs& args) const = 0;
    };

    template<typename... TArgs>
    class Command : public basic_command {
      private:
        std::tuple<TArgs...> getArgs(const CommandArgs& args) const;

      protected:
        virtual cas::math::Expression* operator()(TArgs... args) const = 0;

      public:
        cas::math::Expression* execute(const CommandArgs& args) const override;
    };
} // namespace cas::commands
