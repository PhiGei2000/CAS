#include "commands/commandWrapper.hpp"

#include "io/engine.hpp"

namespace cas::commands {
    void StoreableCommandWrapper::storeVariable(Engine* engine, math::Expression* expr) {
        if (engine->ans != nullptr)
            delete engine->ans;

        engine->ans = expr;
    }
} // namespace cas::commands