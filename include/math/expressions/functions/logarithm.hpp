#pragma once

#include "function.hpp"

namespace cas::math {
    struct Ln : public Function {
      public:
        Expression* argument;

        Ln(const Expression& argument);
        Ln(Expression* argument);

        virtual std::string getName() const override;

        virtual double getValue() const override;
        virtual Expression* copy() const override;

        virtual bool dependsOn(const Variable& var) const override;

        // virtual Expression* simplify() const;

        virtual std::string toString() const override;
    };

    // class Logarithm : public Ln {
    // };
} // namespace cas::math
