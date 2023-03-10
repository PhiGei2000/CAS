#pragma once
#include <sstream>
#include <string>
#include <vector>

namespace cas {
    std::string removeWhiteSpaces(const std::string& str) {
        std::stringstream ss;
        for (auto ch : str) {
            if (!std::isspace(static_cast<unsigned char>(ch))) {
                ss << ch;
            }
        }

        return ss.str();
    }

    std::vector<std::string> splitString(const std::string& str, const char delimiter = ' ') {
        std::vector<std::string> parts;
        std::string part;
        std::stringstream input(str);

        while((std::getline(input, part, delimiter))) {

        }

        return parts;
    }
} // namespace cas
