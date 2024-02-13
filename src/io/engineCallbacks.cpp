#include "io/engine.hpp"

#include "io/ioStream.hpp"

#include <iomanip>

namespace cas {
#pragma region Callbacks
    Command<std::string, std::string> Engine::Callbacks::printStringCallback = Command<std::string, std::string>([](Engine* engine, std::string str) {
        io::IOStream::writeLine(str);

        return str;
    });

    Command<std::string, math::Expression*> Engine::Callbacks::printExpressionCallback = Command<std::string, math::Expression*>([](Engine* engine, math::Expression* expr) {
        std::string str = expr->toString();
        io::IOStream::writeLine(str);

        return str;
    });

    Command<std::string, std::vector<math::ExpressionMatch>> Engine::Callbacks::printExpressionMatchCallback = Command<std::string, std::vector<math::ExpressionMatch>>([](Engine* engine, std::vector<math::ExpressionMatch> matches) {
        std::stringstream ss;
        unsigned int matchesCount = 0;
        for (const auto& match : matches) {
            if (match.success)
                matchesCount++;
        }

        ss << "Found " << matchesCount << " matches" << std::endl;

        const char separator = ' ';
        const int symbolWidth = 10;

        for (const auto match : matches) {
            if (match.success) {
                ss << "Match: " << *match.match << std::endl;
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
            else {
                ss << "No match found";
            }
        }
        std::string result = ss.str();

        io::IOStream::writeLine(result);
        return result;
    });

    void Engine::handleCommandResult(CommandResult& result) {
        switch (result.type) {
            case CommandResult::ResultTypes::STRING:
                Callbacks::printStringCallback.execute(this, result.text);
                break;
            case CommandResult::ResultTypes::EXPRESSION:
                Callbacks::printExpressionCallback.execute(this, result.expr);
                break;
            case CommandResult::ResultTypes::MATCH_LIST:
                Callbacks::printExpressionMatchCallback.execute(this, result.matches);
                break;
        }
    }
#pragma endregion
} // namespace cas