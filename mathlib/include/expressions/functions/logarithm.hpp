#pragma once

#include "function.hpp"

namespace cas::math {
    struct Ln : public Function<1> {
      public:        
        Ln(const Expression& argument);
        Ln(Expression* argument);

        virtual double getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* simplify() const override;

        virtual Expression* getDerivative() const override;
    };

    // class Logarithm : public Ln {
    // };
} // namespace cas::math
