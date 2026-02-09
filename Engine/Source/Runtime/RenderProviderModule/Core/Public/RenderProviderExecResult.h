#pragma once

namespace Rat::RenderProviderModule {
    enum class ExecResult {
        Success = 0,
        IncompatibleDriver = 1,
        UnknownFailure = 2,
        DebugCreationFailed = 3,
        APINotSupported = 4
    };
}