#pragma once

#include "IRenderHardwareProvider.h"
#include "RenderingApi.h"

class IRenderHardwareProviderFactory {
public:
    virtual IRenderHardwareProvider* CreateRenderHardwareProvider(RenderingApi renderingApi, bool* initializationSucceeded) = 0;
    virtual ~IRenderHardwareProviderFactory() = default;
};