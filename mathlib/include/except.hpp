#pragma once

#include <stdexcept>

namespace std {
    class not_implemented_error : public runtime_error {
      public:
        not_implemented_error(const char* message)
            : runtime_error(message) {
        }
    };
} // namespace std