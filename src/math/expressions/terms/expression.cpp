#include "math/expressions/terms/expression.hpp"

#include "math/expressions/terms/variable.hpp"

namespace cas::math {
    Expression::~Expression() {
    }

    Expression* Expression::simplify() const {
        return this->copy();
    }

} // namespace cas::math