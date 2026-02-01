#pragma once

namespace Rat::WindowProviderModule {
    enum class ExecResult {
        Success = 0,
        APIInitializationFailure = 1,
        WindowCreationFailure = 2,
        WindowAlreadyCreated = 3,
        PlatformNotSupported = 4,
    };

    static const char* g_resultDescriptions[] = {
            "Success",
            "Failed to initialize windowing API",
            "Failed to create window",
            "Window already exists"
    };

    const char* GetErrorDescription(ExecResult execResult) {
        return g_resultDescriptions[static_cast<int>(execResult)];
    }
}