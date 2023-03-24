#pragma once

namespace cas::commands {
    template<typename TRes, typename... TArgs>
    using CommandCallback = std::function<void(TRes)>;

    template<typename TRes, typename... TArgs>
    static CommandCallback<TRes> DefaultCallback = [](TRes result) {};
} // namespace cas::commands