#include "math/expressions/functions/function.hpp"

#include "math/expressions/expressions.hpp"

#include <sstream>
#include <vector>

namespace cas::math {
    template<int u>
    bool Function<u>::dependsOn(const Variable& var) const {
        for (const Expression* arg : arguments) {
            if (arg->dependsOn(var)) {
                return true;
            }
        }

        return false;
    }

    template<int u>
    std::string Function<u>::toString() const {
        std::stringstream result;
        result << name << "(" << arguments[0]->toString();

        for (int i = 1; i < u; i++) {
            result << ", " << arguments[i]->toString();
        }

        result << ")";
        return result.str();
    }

    template<int u>
    std::set<Variable> Function<u>::getVariables() const {
        std::set<Variable> vars = arguments[0]->getVariables();
        for (int i = 1; i < u; i++) {
            vars.merge(arguments[i]->getVariables());
        }

        return vars;
    }

    template<int u>
    Expression* Function<u>::differentiate(const Variable* var) const {
        Expression* result = getDerivative();
        
        for (int i = 0; i < u; i++) {
            Expression* dArg = arguments[i]->differentiate(var);
            Multiplication* prod = new Multiplication(result, dArg);
            result = prod;
        }

        return result;
    }

    template bool Function<1>::dependsOn(const Variable&) const;
    template std::string Function<1>::toString() const;
    template std::set<Variable> Function<1>::getVariables() const;
    template Expression* Function<1>::differentiate(const Variable*) const;
} // namespace cas::math
