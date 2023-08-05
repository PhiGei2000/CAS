#include "io/ioStream.hpp"

#include <iostream>
#include <string>

namespace cas::io {
    std::ofstream IOStream::log = std::ofstream("commandLog.log");

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
        write(">");

        std::string input = readLine(';');

        std::string alias;
        std::vector<std::string> argV;

        size_t bracketPosition = input.find('[');
        if (bracketPosition != std::string::npos) {
            // read alias
            alias = input.substr(0, bracketPosition);
            removeWhitespaces(alias);

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

        log << line << delimiter << std::endl;
        return line;
    }

    void IOStream::writeLine(const std::string& str) {
        std::cout << str << std::endl;
        log << str << std::endl;
    }

    void IOStream::write(const std::string& str) {
        std::cout << str;
        log << str;
    }
} // namespace cas::io