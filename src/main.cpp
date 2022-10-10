#include <iostream>

#include "commands/commands.hpp"
#include "io/engine.hpp"

using namespace cas;

void setupCommands(Engine* engine) {
    engine->addCommand<Expression*, Variable*>("D", commands::D());
    engine->addCommand<Expression*>("Df", commands::Df());
    // engine->addCommand("Matches", commands::Matches);
    // engine->addCommand("Match", commands::Match);
}

int main(int argCnt, char** args) {
    Engine engine;

    setupCommands(&engine);

    engine.run();
}
