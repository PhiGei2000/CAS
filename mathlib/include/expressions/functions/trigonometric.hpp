#pragma once

#include "function.hpp"

namespace cas::math {
    struct Sin : public Function<1> {
      public:
        Sin(const Expression& argument);
        Sin(Expression* argument);

        virtual Number getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* getDerivative() const override;
    };

    struct Arcsin : public Function<1> {
      public:
        Arcsin(const Expression& argument);
        Arcsin(Expression* argument);

        virtual Number getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* getDerivative() const override;
    };

    struct Cos : public Function<1> {
      public:
        Cos(const Expression& argument);
        Cos(Expression* argument);

        virtual Number getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* getDerivative() const override;
    };

    struct Arccos : public Function<1> {
      public:
        Arccos(const Expression& argument);
        Arccos(Expression* argument);

        virtual Number getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* getDerivative() const override;
    };

    struct Tan : public Function<1> {
      public:
        Tan(const Expression& argument);
        Tan(Expression* argument);

        virtual Number getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* getDerivative() const override;
    };

    struct Arctan : public Function<1> {
      public:
        Arctan(const Expression& argument);
        Arctan(Expression* argument);

        virtual Number getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* getDerivative() const override;
    };
} // namespace cas::math