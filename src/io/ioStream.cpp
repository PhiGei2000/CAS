#include "io/ioStream.hpp"

#include <iostream>

namespace cas::io {
    void IOStream::removeWhitespaces(std::string& str) {
        for (auto it = str.begin(); it != str.end();) {
            if (*it == '\n' || *it == ' ' || *it == '\t') {
                it = str.erase(it);
            }
            else {
                it++;
            }
        }
    }

    IOStream::Command IOStream::readCommand() {
        std::cout << ">";

        std::string input = readLine(';');
        removeWhitespaces(input);

        std::string alias;
        std::vector<std::string> argV;

        size_t bracketPosition = input.find('[');
        if (bracketPosition != std::string::npos) {
            // read alias
            alias = input.substr(0, bracketPosition);

            // read arguments
            size_t bracketEnd = input.find_last_of(']');
            std::string args = input.substr(bracketPosition + 1, bracketEnd - bracketPosition - 1);

            // split argument string
            size_t current = 0;
            size_t next = args.find(',');
            while (next != std::string::npos) {
                argV.push_back(args.substr(current, next - current));

                current = next + 1;
                next = args.find(',', current);
            }

            // add last argument
            argV.push_back(args.substr(current));
        }
        else {
            alias = input;
        }

        return Command{
            alias,
            argV};
    }

    std::string IOStream::readLine(char delimiter) {
        std::string line;
        std::getline(std::cin, line, delimiter);
        return line;
    }

    void IOStream::writeLine(const std::string& str) {
        std::cout << str << std::endl;
    }
} // namespace cas::io