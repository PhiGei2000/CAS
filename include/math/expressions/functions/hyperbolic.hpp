#pragma once

#include "function.hpp"

namespace cas::math {
    struct Sinh : public Function<1> {
        Sinh(const Expression& argument);
        Sinh(Expression* argument);

        virtual std::string getName() const override;

        virtual double getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* simplify() const override;

        virtual Expression* getDerivative() const override;
    };

    struct Asinh : public Function<1> {
        Asinh(const Expression& argument);
        Asinh(Expression* argument);

        virtual std::string getName() const override;

        virtual double getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* simplify() const override;

        virtual Expression* getDerivative() const override;
    };

    struct Cosh : public Function<1> {
        Cosh(const Expression& argument);
        Cosh(Expression* argument);

        virtual std::string getName() const override;

        virtual double getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* simplify() const override;

        virtual Expression* getDerivative() const override;
    };

    struct Acosh : public Function<1> {
        Acosh(const Expression& argument);
        Acosh(Expression* argument);

        virtual std::string getName() const override;

        virtual double getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* simplify() const override;

        virtual Expression* getDerivative() const override;
    };
}
