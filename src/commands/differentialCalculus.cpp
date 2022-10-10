#include "commands/differentialCalculus.hpp"

#include "math/operators/differential.hpp"

namespace cas::commands {
    Expression* D::operator()(Expression* input, Variable* var) const {
        Expression* simplyfied = input->simplify();

        Expression* derivative = cas::math::D(simplyfied);
        Expression* simplyfiedResult = derivative->simplify();

        delete simplyfied;
        delete derivative;
        return simplyfiedResult;
    }
}
