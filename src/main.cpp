#include <iostream>

#include "io/engine.hpp"
#include "io/commands.hpp"

using namespace cas;


void setupCommands(Engine* engine) {
    engine->addCommand("D", commands::D);
    engine->addCommand("Df", commands::Df);
}

int main(int argCnt, char** args) {
    Engine engine;

    setupCommands(&engine);

    engine.run();
}
