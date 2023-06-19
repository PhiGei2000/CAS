#include "expressions/terms/numeric/complex.hpp"

#include <format>

namespace cas::math {
    Complex::Complex(double real, double imaginary)
        : Number(real), imaginary(imaginary) {
    }

    Complex::Complex(Number number)
        : Number(number), imaginary(0) {
    }

    Number Complex::getValue() const {
        return this;
    }

    Expression* Complex::copy() const {
        return new Complex(realValue, imaginary);
    }    

    std::string Complex::toString() const {
        if (imagiary == 0) {
            return Number::toString();
        }
        else if (imaginary < 0) {
            return std::format("{}{}i", Number::toString(), imaginary);
        }
        else {
            return std::format("{}+{}i", Number::toString(), imaginary);
        }
    }
} // namespace cas::math