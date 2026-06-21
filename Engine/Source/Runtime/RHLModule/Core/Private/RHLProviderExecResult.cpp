#include "../Public/RHLProviderExecResult.h"

namespace Rat::RHLProviderModule {
    const char* g_resultDescriptions[] = {
        "Success",
        "Driver is not compatible with chosen API",
        "Unknown failure",
        "Unable to create debug",
        "PhysicalAdaptorNotFound",
        "AdaptorCreationFailed",
        "IncompatiblePlatform"
    };

    const char* GetErrorDescription(ExecResult execResult) {
        return g_resultDescriptions[static_cast<int>(execResult)];
    }
}