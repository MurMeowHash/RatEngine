#include "../Public/RenderProviderExecResult.h"

namespace Rat::RenderProviderModule {
    const char* g_resultDescriptions[] = {
            "Success",
            "Driver is not compatible with chosen API",
            "Unknown failure",
            "Unable to create debug",
    };

    const char* GetErrorDescription(ExecResult execResult) {
        return g_resultDescriptions[static_cast<int>(execResult)];
    }
}