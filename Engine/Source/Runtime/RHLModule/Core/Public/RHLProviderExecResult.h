#pragma once

namespace Rat::RHLProviderModule {
    enum class ExecResult {
        Success = 0,

        IncompatibleDriver = 1,
        UnknownFailure = 2,
        DebugCreationFailed = 3,
        PhysicalAdaptorNotFound = 4,
        AdaptorCreationFailed = 5,
        IncompatiblePlatform = 6,
    };

    extern const char* g_resultDescriptions[7];

    extern const char* GetErrorDescription(ExecResult execResult);
}