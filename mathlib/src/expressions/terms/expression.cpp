#include "expressions/terms/expression.hpp"

#include "expressions/expressions.hpp"

#if DEBUG
#include "debug/debugTools.hpp"
#include <iostream>
#if WIN32
#include <intrin.h>
#endif
#endif

namespace cas::math {
    no_value_error::no_value_error(const std::string& message)
        : std::runtime_error(message) {
    }

#if DEBUG
    unsigned int Expression::expressionCounter = 0;

    Expression::Expression() {
        expressionCounter++;

        memLog << "created expression " << (void*)this << " total:" << expressionCounter << " "
#if WIN32
               << _ReturnAddress()
#else
               << __builtin_return_address(0)
#endif               
               << std::endl;
    }
#endif

    Expression::~Expression() {
#if DEBUG
        expressionCounter--;
        memLog << "deleted expression " << (void*)this << " total:" << expressionCounter << " "
#if WIN32
               << _ReturnAddress()
#else
               << __builtin_return_address(0)
#endif
               << std::endl;
#endif
    }

    std::vector<Expression*> Expression::getChildren() const {
        return {};
    }

    Expression* Expression::simplify() const {
        return this->copy();
    }

    Expression* Expression::getRoot() {
        if (parent == nullptr)
            return this;

        return parent->getRoot();
    }

    void Expression::replace(Expression* expr, Expression* newExpr) {
    }

    void Expression::setVariable(Variable* symbol, Expression* expr) {
    }

    Expression* assign(Expression* other, Expression* parent) {
        Expression* expr;
        if (other->parent == nullptr || other->parent == parent) {
            expr = other;
        }
        else {
            expr = other->copy();
        }
        expr->parent = parent;
        return expr;
    }

    std::ostream& operator<<(std::ostream& os, const Expression& expr) {
        return os << expr.toString();
    }

    std::ostream& operator<<(std::ostream& os, Expression* expr) {
        return os << expr->toString();
    }
} // namespace cas::math