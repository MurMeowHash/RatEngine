#include "../Public/WindowProviderExecResult.h"

namespace Rat::WindowProviderModule {
    const char* g_resultDescriptions[] = {
            "Success",
            "Failed to initialize windowing API",
            "Failed to create window",
            "Window already exists",
            "Window provider does not exist for this platform"
    };

    const char* GetErrorDescription(ExecResult execResult) {
        return g_resultDescriptions[static_cast<int>(execResult)];
    }
}