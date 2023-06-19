#pragma once
#include "expressions/terms/number.hpp"
#include "expressions/terms/numeric/complex.hpp"

#include <numbers>

namespace cas::math {
    struct NamedConstant : public Number {
      protected:
        std::string symbol;

      public:
        inline NamedConstant(const std::string& symbol, Number value)
            : Number(value), symbol(symbol) {
        }

        inline virtual Expression* copy() const override {
            return new NamedConstant(symbol, realValue);
        }

        inline virtual ExpressionTypes getType() const override {
            return ExpressionTypes::NamedConstant;
        }

        inline virtual std::string toString() const override {
            return symbol;
        }
    };

    struct E : public NamedConstant {
      public:
        inline E()
            : NamedConstant("e", std::numbers::e) {
        }
    };

    struct I : public NamedConstant {
        inline I()
            : NamedConstant("i", Complex(0, 1)) {
        }
    };
} // namespace cas::math