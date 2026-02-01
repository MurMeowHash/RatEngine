#pragma once

namespace Rat::Core {
    enum class ErrorSeverity {
        Success = 0,
        Fatal = 1,
        Warning = 2
    };

    bool g_isEngineQuitRequested = false;
}
