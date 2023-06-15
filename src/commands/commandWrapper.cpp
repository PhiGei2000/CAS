#include "commands/commandWrapper.hpp"

#include "io/engine.hpp"

namespace cas::commands {
    void CommandWrapper::saveAns(Engine* engine, Expression* expr) {
        if (engine->ans != nullptr) {
            delete engine->ans;
        }

        engine->ans = expr;
    }
} // namespace cas::commands