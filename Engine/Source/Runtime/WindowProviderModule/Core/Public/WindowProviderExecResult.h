#pragma once

namespace Rat::WindowProviderModule {
    enum class ExecResult {
        Success = 0,
        APIInitializationFailure = 1,
        WindowCreationFailure = 2,
        WindowAlreadyCreated = 3,
        PlatformNotSupported = 4,
    };

    extern const char* g_resultDescriptions[5];

    extern const char* GetErrorDescription(ExecResult execResult);
}