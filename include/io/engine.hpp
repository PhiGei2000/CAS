#pragma once
#include <functional>
#include <string>
#include <unordered_map>

#include "commands/commandDelegate.hpp"

using namespace cas::commands;

namespace cas {    

    class Engine {
      private:        
        std::unordered_map<std::string, CommandDelegate> commands;

      public:
        void addCommand(const std::string& alias, CommandDelegate delegate);

        void run() const;
    };
} // namespace cas