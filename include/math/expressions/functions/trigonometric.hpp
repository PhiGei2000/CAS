#pragma once

#include "function.hpp"

namespace cas::math {
    struct Sin : public Function {
      public:
        Expression* argument;

        Sin(const Expression& argument);
        Sin(Expression* argument);

        virtual std::string getName() const override;

        virtual double getValue() const override;
        virtual Expression* copy() const override;

        virtual bool dependsOn(const Variable& var) const override;

        virtual std::string toString() const override;

        virtual std::unordered_set<Variable> getVariables() const override;
    };

    struct Cos : public Function {
      public:
        Expression* argument;

        Cos(const Expression& argument);
        Cos(Expression* argument);

        virtual std::string getName() const override;

        virtual double getValue() const override;
        virtual Expression* copy() const override;

        virtual bool dependsOn(const Variable& var) const override;

        virtual std::string toString() const override;

        virtual std::unordered_set<Variable> getVariables() const override;
    };
} // namespace cas::math