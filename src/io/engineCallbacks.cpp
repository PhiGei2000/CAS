#include "io/engine.hpp"

#include "io/ioStream.hpp"

#include <iomanip>

namespace cas {
    #pragma region Callbacks
        CommandCallback<std::string> Engine::Callbacks::printStringCallback = [](std::string str) {
            io::IOStream::writeLine(str);
        };

        CommandCallback<math::Expression*> Engine::Callbacks::printExpressionCallback = [](math::Expression* expr) {
            io::IOStream::writeLine(expr->toString());
        };

        CommandCallback<math::ExpressionMatch> Engine::Callbacks::printExpressionMatchCallback = [](math::ExpressionMatch match) {
            std::stringstream ss;

            const char separator = ' ';
            const int symbolWidth = 10;

            ss << std::left << std::setw(symbolWidth) << std::setfill(separator) << "Variable"
               << " | "
               << "Value";

            for (const auto& [var, expr] : match.variables) {
                ss << std::endl;
                ss << std::left << std::setw(symbolWidth) << std::setfill(separator) << var << " | ";
                ss << expr->toString();
            }

            io::IOStream::writeLine(ss.str());
        };

        CommandCallback<std::vector<math::ExpressionMatch>> Engine::Callbacks::printExpressionMatchesCallback = [](std::vector<math::ExpressionMatch> matches) {
            std::stringstream ss;
            ss << "Found " << matches.size() << " matches" << std::endl;

            const char separator = ' ';
            const int symbolWidth = 10;

            for (const auto match : matches) {
                ss << "Match: " << *match.node << std::endl;
                ss << std::left << std::setw(symbolWidth) << std::setfill(separator) << "Variable"
                   << " | "
                   << "Value";

                for (const auto& [var, expr] : match.variables) {
                    ss << std::endl;
                    ss << std::left << std::setw(symbolWidth) << std::setfill(separator) << var << " | ";
                    ss << expr->toString();
                }
                ss << std::endl;
            }
            io::IOStream::writeLine(ss.str());
        };
#pragma endregion
}