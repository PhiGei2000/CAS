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
        return parseCommand(input);
    }

    IOStream::Command IOStream::parseCommand(const std::string& input) {
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
            auto it = args.begin();

            size_t begin = 0;
            size_t end;

            int bracketCounter = 0;
            while (it != args.end()) {
                if (*it == '[') {
                    bracketCounter++;
                }
                else if (*it == ']') {
                    bracketCounter--;
                }
                else if (*it == ',' && bracketCounter == 0) {
                    end = it - args.begin();

                    argV.push_back(args.substr(begin, end - begin));
                    begin = end + 1;
                }

                it++;
            }

            argV.push_back(args.substr(begin));
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