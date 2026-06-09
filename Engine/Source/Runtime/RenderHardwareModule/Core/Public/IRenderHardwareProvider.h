#pragma once

#include <cstdint>
#include "RenderHardwareProviderExecResult.h"

class IRenderHardwareProvider {
public:
    [[nodiscard]] virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;
    virtual ~IRenderHardwareProvider() = default;
};