#pragma once

#include <cstdint>

class IPlatformInteractor {
public:
    virtual void RequestQuit(bool forcedQuit) = 0;
    [[nodiscard]] virtual uint32_t GetRunningThreadId() = 0;
    virtual ~IPlatformInteractor() = default;
};