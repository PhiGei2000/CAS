#pragma once
#include "expressions/terms/number.hpp"

namespace cas::math {
    struct Complex : public Number {
        double imaginary;

        Complex(double real, double imaginary);
        Complex(Number number);

        virtual Number getValue() const override;
        virtual Expression* copy() const override;

        virtual std::string toString() const override;

        Complex operator-() const;
        Complex operator+(const Complex& other) const;
        Complex operator-(const Complex& other) const;
        Complex operator*(const Complex& other) const;
        Complex operator/(const Complex& other) const;

        operator double() const = delete;
    };
} // namespace cas::math