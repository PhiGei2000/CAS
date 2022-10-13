#pragma once
#include <string>

namespace cas {
    std::string& removeWhiteSpaces(std::string& str) {
        std::size_t pos = 0;
        while (pos < str.size()) {
            if (!std::isspace(str.at(pos))) {
                pos++;
                continue;
            }

            str.erase(pos, 1);
        }

        return str;
    }
} // namespace cas
