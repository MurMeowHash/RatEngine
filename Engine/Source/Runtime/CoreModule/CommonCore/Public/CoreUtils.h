#pragma once

#include <string>
#include <sstream>

#define StringFormatter(...) Rat::Core::StringFormatter::FormatString(__VA_ARGS__)

namespace Rat::Core::StringFormatter {
    template<typename... Args>
    std::string FormatString(const Args&... args) {
        std::ostringstream oss;
        ((oss << args), ...);
        return oss.str();
    }
}