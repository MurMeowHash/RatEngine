#pragma once

#include <cstdint>
#include "PlatformRuntimeData.h"

class IPlatformInteractor {
public:
    virtual void RequestQuit(bool forcedQuit) = 0;
    [[nodiscard]] virtual uint32_t GetRunningThreadId() = 0;
    [[nodiscard]] virtual PlatformRuntimeData GetPlatformRuntimeData() = 0;
    virtual ~IPlatformInteractor() = default;
};