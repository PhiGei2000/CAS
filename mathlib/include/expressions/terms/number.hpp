#pragma once

#include "expression.hpp"

#include <cmath>

namespace cas::math {

    struct Number : public Expression {
        double realValue;

        Number(double realValue);

        virtual Number getValue() const override;
        virtual Expression* copy() const override;
        virtual ExpressionTypes getType() const override;

        virtual bool dependsOn(const Variable& var) const override;

        virtual Expression* differentiate(const Variable* var) const override;

        virtual std::string toString() const override;

        virtual std::set<Variable> getVariables() const override;
        
        inline operator double() const {
            return realValue;
        }
    };

    template<typename T>
    concept NumericType = std::is_base_of_v<Number, T>;
} // namespace cas::math
