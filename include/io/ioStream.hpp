#pragma once
#include <istream>
#include <vector>

namespace cas::io {
    class IOStream {
      protected:
        static void removeWhitespaces(std::string& str);
        
      public:
        struct Command {
            std::string alias;
            std::vector<std::string> args;
        };

        static Command readCommand();

        static std::string readLine(char delimiter = '\n');
    };
} // namespace cas::io