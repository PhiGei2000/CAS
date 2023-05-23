#pragma once

#include "function.hpp"

namespace cas::math {
    struct Sinh : public Function<1> {
        const std::string name = "sinh";

        Sinh(const Expression& argument);
        Sinh(Expression* argument);

        virtual Number getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* simplify() const override;

        virtual Expression* getDerivative() const override;
    };

    struct Asinh : public Function<1> {
        const std::string name = "asinh";

        Asinh(const Expression& argument);
        Asinh(Expression* argument);

        virtual Number getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* simplify() const override;

        virtual Expression* getDerivative() const override;
    };

    struct Cosh : public Function<1> {
        const std::string name = "cosh";
        Cosh(const Expression& argument);
        Cosh(Expression* argument);

        virtual Number getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* simplify() const override;

        virtual Expression* getDerivative() const override;
    };

    struct Acosh : public Function<1> {
        const std::string name = "acosh";

        Acosh(const Expression& argument);
        Acosh(Expression* argument);

        virtual Number getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* simplify() const override;

        virtual Expression* getDerivative() const override;
    };
} // namespace cas::math
