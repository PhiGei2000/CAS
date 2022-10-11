#include "commands/differentialCalculus.hpp"

#include "math/operators/differential.hpp"

namespace cas::commands {
    Expression* D::operator()(Expression* input, Variable* var) const {
        return cas::math::D(input, *var);                
    }

    Expression* Df::operator()(Expression* input) const {
        return cas::math::D(input);
    }
}
