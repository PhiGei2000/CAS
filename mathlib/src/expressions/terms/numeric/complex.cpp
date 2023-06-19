#include "expressions/terms/numeric/complex.hpp"

#include <sstream>
#include <numbers>

namespace cas::math {
    Complex::Complex(double real)
        : Complex(real, 0) {
    }

    Complex::Complex(double real, double imaginary)
        : Number(real), imaginary(imaginary) {
    }

    Complex::Complex(Number number)
        : Number(number), imaginary(0) {
    }

    Complex Complex::fromPolar(double abs, double arg) {
        return Complex(abs * cos(arg), abs * sin(arg));
    }

    Number Complex::getValue() const {
        return *this;
    }

    Expression* Complex::copy() const {
        return new Complex(realValue, imaginary);
    }

    Number Complex::conjugate() const {
        return Complex(realValue, -imaginary);
    }

    double Complex::abs() const {
        return std::sqrt(realValue * realValue + imaginary * imaginary);
    }

    double Complex::arg() const {
        return atan2(imaginary, realValue);
    }

    std::string Complex::toString() const {
        std::stringstream ss;
        ss << realValue;

        if (imaginary > 0) {
            ss << "+" << imaginary << "i";
        }
        else if (imaginary < 0) {
            ss << imaginary << "i";
        }

        return ss.str();
    }

    Complex Complex::operator-() const {
        return Complex(-realValue, -imaginary);
    }

    Complex Complex::operator+(const Complex& other) const {
        return Complex(realValue + other.realValue, imaginary + other.imaginary);
    }

    Complex Complex::operator-(const Complex& other) const {
        return Complex(realValue - other.realValue, imaginary - other.imaginary);
    }

    Complex Complex::operator*(const Complex& other) const {
        return Complex(
            realValue * other.realValue - imaginary * other.imaginary,
            realValue * other.imaginary + imaginary * other.realValue);
    }

    Complex Complex::operator/(const Complex& other) const {
        Number denominator = other.realValue * other.realValue + other.imaginary * other.imaginary;

        return *this * other.conjugate() / denominator;
    }

    Complex exp(const Complex& c) {
        // exp(x+iy) = exp(x)*[cos(y)+i sin(y)]
        return (Complex)std::exp(c.realValue) * Complex(cos(c.imaginary), sin(c.imaginary));
    }

    Complex ln(const Complex& c) {
        // z=re^(ip)=exp(ln(r)+ip))=exp(ln(z)) => ln(z) = ln(re^(ip)) = ln(r)+ip
        return Complex(std::log(c.abs()), c.arg());
    }

    std::vector<Complex> sqrt(const Complex& c, int n) {
        std::vector<Complex> result;
        result.reserve(n);

        double resAbs = std::pow(c.abs(), 1.0 / n);
        double arg = c.arg();
        for (int i = 0; i < n; i++) {
            double resArg = (arg + 2 * std::numbers::pi * i / n);
            result.push_back(Complex::fromPolar(resAbs, resArg));
        }

        return result;
    }
} // namespace cas::math