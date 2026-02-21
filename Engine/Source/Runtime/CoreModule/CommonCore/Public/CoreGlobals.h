#pragma once

#include <type_traits>
#include <cstdint>

namespace Rat::Core {
    inline static const int InvalidIndex = -1;

    enum class ErrorSeverity {
        Success = 0,
        Fatal = 1,
        Warning = 2
    };

    extern bool g_isEngineQuitRequested;
}
