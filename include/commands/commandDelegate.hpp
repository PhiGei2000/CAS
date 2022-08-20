#pragma once
#include "commandArgs.hpp"

#include <functional>
#include <string>

namespace cas::commands {
    typedef std::function<std::string(const CommandArgs&)> CommandDelegate;
}
