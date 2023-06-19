#pragma once
#include "expressions/terms/number.hpp"

namespace cas::math {
    struct Complex : public Number {
        double imaginary;

        Complex(double real);
        Complex(double real, double imaginary);
        Complex(Number number);
        static Complex fromPolar(double abs, double arg);

        virtual Number getValue() const override;
        virtual Expression* copy() const override;

        virtual Number conjugate() const;
        virtual double abs() const;
        virtual double arg() const;

        virtual std::string toString() const override;

        Complex operator-() const;
        Complex operator+(const Complex& other) const;
        Complex operator-(const Complex& other) const;
        Complex operator*(const Complex& other) const;
        Complex operator/(const Complex& other) const;

        operator double() const = delete;
    };    

    Complex exp(const Complex& c);
    Complex ln(const Complex& c);

    std::vector<Complex> sqrt(const Complex& c, int n);
} // namespace cas::math