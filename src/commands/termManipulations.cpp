#include "commands/termManipulation.hpp"

namespace cas::commands {
    Expression* Simplify::operator()(Expression* expr) const {
        return expr;
    }
}