#pragma once

#include "function.hpp"

namespace cas::math {
    struct Sin : public Function<1> {
      public:
        Sin(const Expression& argument);
        Sin(Expression* argument);

        virtual std::string getName() const override;

        virtual double getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* differentiate(const Variable* var) const override;
    };

    struct Cos : public Function<1> {
      public:
        Cos(const Expression& argument);
        Cos(Expression* argument);

        virtual std::string getName() const override;

        virtual double getValue() const override;
        virtual Expression* copy() const override;        

        virtual Expression* differentiate(const Variable* var) const override;
    };

    struct Tan : public Function<1> {
      public:
        Tan(const Expression& argument);
        Tan(Expression* argument);

        virtual std::string getName() const override;

        virtual double getValue() const override;
        virtual Expression* copy() const override;

        virtual Expression* differentiate(const Variable* var) const override;
    };
} // namespace cas::math