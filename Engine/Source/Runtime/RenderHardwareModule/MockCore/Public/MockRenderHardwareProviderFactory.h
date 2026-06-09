#pragma once

#include "IRenderHardwareProviderFactory.h"

class MockRenderHardwareProviderFactory : public IRenderHardwareProviderFactory {
public:
    IRenderHardwareProvider* CreateRenderHardwareProvider(RenderingApi renderingApi, bool* initializationSucceeded) override;
};