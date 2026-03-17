#pragma once

namespace Rat::RenderProviderModule {
    enum class ExecResult {
        Success = 0,
        IncompatibleDriver = 1,
        UnknownFailure = 2,
        DebugCreationFailed = 3,
        PhysicalAdaptorNotFound = 4,
        AdaptorCreationFailed = 5,
    };

    extern const char* g_resultDescriptions[4];

    extern const char* GetErrorDescription(ExecResult execResult);
}