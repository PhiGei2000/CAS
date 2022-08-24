#include <iostream>

#include "io/engine.hpp"
#include "commands/commands.hpp"

using namespace cas;


void setupCommands(Engine* engine) {
    engine->addCommand("D", commands::D);
    engine->addCommand("Df", commands::Df);
    engine->addCommand("Matches", commands::Matches);
    engine->addCommand("Match", commands::Match);
}

int main(int argCnt, char** args) {
    Engine engine;

    setupCommands(&engine);

    engine.run();
}
