#include "math/expressions/expression.hpp"

#include "math/expressions/variable.hpp"

namespace cas::math
{

Expression* Expression::simplify() const {
    return this->copy();
}

} // namespace cas::math