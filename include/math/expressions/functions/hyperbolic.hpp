#pragma once

#include "function.hpp"

namespace cas::math {
    struct Sinh : public Function<1> {
        Sinh(const Expression& argument);
        Sinh(Expression* argument);

        virtual std::string getName() const override;

        virtual double getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* differentiate(const Variable* var) const override;
    };

    struct Cosh : public Function<1> {
        Cosh(const Expression& argument);
        Cosh(Expression* argument);

        virtual std::string getName() const override;

        virtual double getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* differentiate(const Variable* var) const override;
    };
}
