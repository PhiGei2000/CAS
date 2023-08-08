#pragma once
#include <istream>
#include <vector>
#include <fstream>

namespace cas::io {
    class IOStream {
      protected:
        static void removeWhitespaces(std::string& str);

        static std::ofstream log;

      public:
        struct Command {
            std::string alias;
            std::vector<std::string> args;
        };

        static Command readCommand();

        static Command parseCommand(const std::string& str);

        static std::string readLine(char delimiter = '\n');

        static void writeLine(const std::string& str);

        static void write(const std::string& str);
    };
} // namespace cas::io