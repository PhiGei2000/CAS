#include "commands/differentialCalculus.hpp"

#include "expressions/expressions.hpp"

namespace cas::commands {
    Expression* D::operator()(Expression* input, Variable* var) const {
        return input->differentiate(var);
    }

    Expression* Df::operator()(Expression* input) const {
        Expression* result = new Constant(0);
        std::set<Variable> vars = input->getVariables();

        if (vars.size() > 0) {
            delete result;

            auto it = vars.begin();
            result = new Multiplication(input->differentiate(&(*it)), new Differential(it->getSymbol()));
            it++;

            while(it != vars.end()) {
                Expression* d = new Multiplication(input->differentiate(&(*it)), new Differential(it->getSymbol()));
                Expression* tmp = new Addition(result, d);

                result = tmp;
                it++;
            }
        }

        return result;
    }
}
