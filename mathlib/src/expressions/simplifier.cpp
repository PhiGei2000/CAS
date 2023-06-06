#include "expressions/simplifier.hpp"

#include <math.h>
#include <stdexcept>

namespace cas::math {

#pragma region ProductParts
    void Simplifier::ProductParts::multiply(const Simplifier::ProductParts& parts) {
        coefficient *= parts.coefficient;

        for (const auto& [var, exp] : parts.variables) {
            variables[var] += exp;
        }

        for (const auto& term : parts.restTerms) {
            restTerms.push_back(term);
        }
    }

    void Simplifier::ProductParts::power(double exponent) {
        coefficient = pow(coefficient, exponent);

        for (const auto& [var, _] : variables) {
            variables[var] *= exponent;
        }

        std::vector<Expression*> poweredTerms;
        for (auto term : restTerms) {
            Exponentiation* power = new Exponentiation(term, new Number(exponent));

            poweredTerms.push_back(power);
        }

        restTerms = poweredTerms;
    }

    bool Simplifier::ProductParts::areLike(const Simplifier::ProductParts& first, const Simplifier::ProductParts& second) {
        if (first.variables.size() != second.variables.size())
            return false;

        for (const auto& [var, exp] : first.variables) {
            try {
                if (second.variables.at(var) != exp) {
                    return false;
                }
            }
            catch (const std::out_of_range&) {
                return false;
            }
        }

        return true;
    }
#pragma endregion

    Expression* Simplifier::simplify(const Expression* expr) {
        ExpressionTypes type = expr->getType();

        switch (type) {
            case ExpressionTypes::Addition:
                return simplifyAddition(reinterpret_cast<const Addition*>(expr));
            case ExpressionTypes::Multiplication:
                return simplifyMultiplication(reinterpret_cast<const Multiplication*>(expr));
            default:
                return expr->copy();
        }
    }

    Simplifier::ProductParts Simplifier::getProductParts(const Multiplication* prod) noexcept(false) {
        ProductParts parts;

        ExpressionTypes leftType = prod->left->getType();
        ExpressionTypes rightType = prod->right->getType();

        switch (leftType) {
            case ExpressionTypes::Addition:
                throw std::runtime_error("Can not get product parts if the product contains a addition as factor");

            case ExpressionTypes::Multiplication: {
                ProductParts leftParts = getProductParts(reinterpret_cast<Multiplication*>(prod->left));

                parts.multiply(leftParts);
            } break;

            case ExpressionTypes::Exponentiation: {
                Exponentiation* exp = reinterpret_cast<Exponentiation*>(prod->left);
                try {
                    ProductParts leftParts = getExpProductParts(exp);
                    parts.multiply(leftParts);
                }
                catch (const std::runtime_error&) {
                    parts.restTerms.push_back(exp->copy());
                }

            } break;

            case ExpressionTypes::Constant: {
                Number* c = reinterpret_cast<Number*>(prod->left);
                parts.coefficient *= c->getValue().realValue;
            } break;

            case ExpressionTypes::Variable: {
                Variable* v = reinterpret_cast<Variable*>(prod->left);
                parts.variables[v->getSymbol()] += 1;
            } break;

            default: {
                parts.restTerms.push_back(prod->left->copy());
            } break;
        }

        switch (rightType) {
            case ExpressionTypes::Addition:
                throw std::runtime_error("Can not get product parts if the product contains a addition as factor");

            case ExpressionTypes::Multiplication: {
                ProductParts rightParts = getProductParts(reinterpret_cast<Multiplication*>(prod->right));

                parts.multiply(rightParts);
            } break;

            case ExpressionTypes::Exponentiation: {
                Exponentiation* exp = reinterpret_cast<Exponentiation*>(prod->right);
                ProductParts rightParts = getExpProductParts(exp);

                parts.multiply(rightParts);
            } break;

            case ExpressionTypes::Constant: {
                Number* c = reinterpret_cast<Number*>(prod->right);
                parts.coefficient *= c->getValue().realValue;
            } break;

            case ExpressionTypes::Variable: {
                Variable* v = reinterpret_cast<Variable*>(prod->right);
                parts.variables[v->getSymbol()] += 1;
            } break;

            default: {
                parts.restTerms.push_back(prod->right->copy());
            } break;
        }

        return parts;
    }

    Simplifier::ProductParts Simplifier::getExpProductParts(const Exponentiation* exp) noexcept(false) {
        ProductParts parts;
        double exponent = NAN;
        try {
            exponent = exp->right->getValue().realValue;
        }
        catch (std::exception e) {
            throw std::runtime_error("Only constants are allowed as exponents");
        }

        ExpressionTypes baseType = exp->left->getType();
        switch (baseType) {
            case ExpressionTypes::Addition:
                throw std::runtime_error("Can not get product parts if the product contains a addition as factor");

            case ExpressionTypes::Multiplication: {
                ProductParts baseParts = getProductParts(reinterpret_cast<Multiplication*>(exp->left));
                baseParts.power(exponent);

                parts.multiply(baseParts);
            } break;

            case ExpressionTypes::Exponentiation: {
                Exponentiation* innerExp = reinterpret_cast<Exponentiation*>(exp->left);
                ProductParts baseParts = getExpProductParts(innerExp);

                baseParts.power(exponent);
                parts.multiply(baseParts);
            } break;

            case ExpressionTypes::Constant: {
                Number* c = reinterpret_cast<Number*>(exp->left);

                parts.coefficient *= pow(c->getValue().realValue, exponent);
            } break;

            case ExpressionTypes::Variable: {
                Variable* v = reinterpret_cast<Variable*>(exp->left);

                parts.variables[v->getSymbol()] += exponent;
            } break;

            default:
                parts.restTerms.push_back(exp->copy());
                break;
        }

        return parts;
    }

    Expression* Simplifier::getProductFromParts(const Simplifier::ProductParts& parts) {
        if (parts.variables.size() == 0 && parts.restTerms.size() == 0) {
            return new Number(parts.coefficient);
        }

        Expression* result = nullptr;
        if (parts.variables.size() > 0) {
            auto getTerm = [&](std::unordered_map<VariableSymbol, double>::const_iterator it) -> Expression* {
                double exp = (*it).second;
                if (exp == 1) {
                    return new Variable((*it).first);
                }
                else if (exp == 0) {
                    return new Number(0);
                }

                Number* exponent = new Number(exp);
                Variable* variable = new Variable((*it).first);

                return new Exponentiation(variable, exponent);
            };

            auto it = parts.variables.begin();

            while (it != parts.variables.end()) {
                if (result == nullptr) {
                    result = getTerm(it);
                }
                else {
                    Multiplication* p = new Multiplication(getTerm(it), result);
                    result = p;
                }
                it++;
            }
        }

        if (parts.restTerms.size() > 0) {
            auto it = parts.restTerms.begin();
            while (it != parts.restTerms.end()) {
                if (result == nullptr) {
                    result = (*it)->copy();
                }
                else {
                    Multiplication* p = new Multiplication(*it, result);
                    result = p;
                }
                it++;
            }
        }

        if (parts.coefficient != 1) {
            Number* coefficient = new Number(parts.coefficient);
            Multiplication* p = new Multiplication(coefficient, result);
            result = p;
        }
        return result;
    }

    void Simplifier::getSummands(const Expression* expr, std::vector<Expression*>* summands) {
        if (expr->getType() == ExpressionTypes::Addition) {
            const Addition* sum = reinterpret_cast<const Addition*>(expr);

            if (sum->left->getType() == ExpressionTypes::Addition) {
                const Addition* leftSum = reinterpret_cast<const Addition*>(sum->left);
                getSummands(leftSum, summands);
            }
            else {
                summands->push_back(sum->left->copy());
            }

            if (sum->right->getType() == ExpressionTypes::Addition) {
                const Addition* rightSum = reinterpret_cast<const Addition*>(sum->right);
                getSummands(rightSum, summands);
            }
            else {
                summands->push_back(sum->right->copy());
            }
        }
        else {
            summands->push_back(expr->copy());
        }
    }

    Expression* Simplifier::multiplyOut(const Expression* left, const Expression* right) {
        std::vector<Expression*> leftSummands, rightSummands;

        getSummands(left, &leftSummands);
        getSummands(right, &rightSummands);

        std::vector<Expression*> resultSummands;
        for (const auto& leftSummand : leftSummands) {
            for (const auto& rightSummand : rightSummands) {
                Multiplication* summand = new Multiplication(*leftSummand, *rightSummand);

                resultSummands.push_back(summand->simplify());
                delete summand;
            }
        }

        auto it = resultSummands.rbegin();
        Expression* result = *it;
        it++;

        while (it != resultSummands.rend()) {
            Addition* sum = new Addition(*it, result);
            result = sum;

            it++;
        }

        return result;
    }

    Expression* Simplifier::simplifyAddition(const Addition* sum) {
        // simplify both summands
        Expression* left = sum->left->simplify();
        Expression* right = sum->right->simplify();

        // evaluate numerical values if the summands are constants
        if (left->getType() == ExpressionTypes::Constant) {
            double leftValue = left->getValue().realValue;
            if (right->getType() == ExpressionTypes::Constant) {
                double value = leftValue + right->getValue().realValue;

                return new Number(value);
            }
            // ignore first summand if it is zero
            else if (leftValue == 0) {
                return right;
            }
        }

        // ignore second summand if it is zero
        if (right->getType() == ExpressionTypes::Constant) {
            double rightValue = right->getValue().realValue;
            if (rightValue == 0)
                return left;
        }

        Addition* simplifiedSum = new Addition(left, right);
        // if (left->getType() == ExpressionTypes::Addition || right->getType() == ExpressionTypes::Addition) {
        std::vector<Expression*> summands;
        getSummands(simplifiedSum, &summands);

        std::vector<ProductParts> combinedTerms;
        for (const auto& summand : summands) {
            ExpressionTypes type = summand->getType();

            switch (type) {
                case ExpressionTypes::Exponentiation: {
                    try {
                        ProductParts parts = getExpProductParts(reinterpret_cast<const Exponentiation*>(summand));

                        auto it = combinedTerms.begin();
                        while (it != combinedTerms.end()) {
                            if (ProductParts::areLike(*it, parts)) {
                                break;
                            }

                            it++;
                        }

                        if (it == combinedTerms.end()) {
                            combinedTerms.push_back(parts);
                        }
                        else {
                            (*it).coefficient += parts.coefficient;
                        }
                    }
                    catch (const std::runtime_error&) {
                        combinedTerms.push_back(ProductParts{1, {}, {summand}});
                    }
                } break;
                case ExpressionTypes::Multiplication: {
                    ProductParts parts = getProductParts(reinterpret_cast<const Multiplication*>(summand));

                    auto it = combinedTerms.begin();
                    while (it != combinedTerms.end()) {
                        if (ProductParts::areLike(*it, parts)) {
                            break;
                        }

                        it++;
                    }

                    if (it == combinedTerms.end()) {
                        combinedTerms.push_back(parts);
                    }
                    else {
                        (*it).coefficient += parts.coefficient;
                    }
                } break;

                case ExpressionTypes::Constant: {
                    double value = summand->getValue().realValue;

                    // find term without variables
                    auto it = combinedTerms.begin();
                    while (it != combinedTerms.end()) {
                        if ((*it).variables.size() == 0)
                            break;

                        it++;
                    }

                    if (it == combinedTerms.end()) {
                        combinedTerms.push_back(ProductParts{value, {}});
                    }
                    else {
                        (*it).coefficient += value;
                    }
                } break;

                case ExpressionTypes::NamedConstant:
                case ExpressionTypes::Variable: {
                    const Variable* var = reinterpret_cast<const Variable*>(summand);
                    ProductParts parts = ProductParts{1, std::unordered_map<VariableSymbol, double>{{var->getSymbol(), 1}}, {}};

                    auto it = combinedTerms.begin();
                    while (it != combinedTerms.end()) {
                        if (ProductParts::areLike(*it, parts)) {
                            break;
                        }

                        it++;
                    }

                    if (it == combinedTerms.end()) {
                        combinedTerms.push_back(parts);
                    }
                    else {
                        (*it).coefficient += parts.coefficient;
                    }
                } break;
                default: {
                    combinedTerms.push_back(ProductParts{1, {}, {summand}});
                } break;
            }
        }

        Expression* result = nullptr;
        auto it = combinedTerms.rbegin();

        while (it != combinedTerms.rend()) {
            if (result == nullptr) {
                result = getProductFromParts(*it);
            }
            else {
                Addition* sum = new Addition(getProductFromParts(*it), result);
                result = sum;
            }

            it++;
        }

        return result;
        // }

        return simplifiedSum;
    }

    Expression* Simplifier::simplifyMultiplication(const Multiplication* prod) {
        // simplyfy both factors
        Expression* left = prod->left->simplify();
        Expression* right = prod->right->simplify();

        // evaluate numerical values if the factors are constants
        if (left->getType() == ExpressionTypes::Constant) {
            double leftValue = left->getValue().realValue;
            if (right->getType() == ExpressionTypes::Constant) {
                double value = leftValue * right->getValue().realValue;
                return new Number(value);
            }
            // ignore fist factor if it is one
            else if (leftValue == 1) {
                return right;
            }
            // if one factor is zero then the product is zero
            else if (leftValue == 0) {
                return new Number(0);
            }
        }

        if (right->getType() == ExpressionTypes::Constant) {
            double rightValue = right->getValue().realValue;

            // ignore second factor if it is one
            if (rightValue == 1) {
                return left;
            }
            // if one factor is zero then the product is zero
            else if (rightValue == 0) {
                return new Number(0);
            }
        }

        // multiply out
        if (left->getType() == ExpressionTypes::Addition || right->getType() == ExpressionTypes::Addition) {
            Expression* sum = multiplyOut(left, right);

            return sum->simplify();
        }

        // create new product whit the simplified terms
        Multiplication* simplifiedProduct = new Multiplication(left, right);
        try {
            // reorder terms
            ProductParts parts = getProductParts(simplifiedProduct);
            delete simplifiedProduct;

            return getProductFromParts(parts);
        }
        catch (const std::runtime_error&) {
            return simplifiedProduct;
        }
    }

    Expression* Simplifier::simplifyExponentiation(const Exponentiation* exp) {
        Expression* left = exp->left->simplify();
        Expression* right = exp->right->simplify();

        if (right->getType() == ExpressionTypes::Constant) {
            double value = right->getValue().realValue;

            if (left->getType() == ExpressionTypes::Constant) {
                return new Number(pow(left->getValue().realValue, value));
            }

            if (value == 0)
                return new Number(1);
            else if (value == 1)
                return left;
        }

        return new Exponentiation(left, right);
    }
} // namespace cas::math