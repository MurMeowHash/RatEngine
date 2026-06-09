#pragma once

#include "IRenderHardwareProviderFactory.h"
#include "DiContainer.h"

class WindowsRenderHardwareProviderFactory : public IRenderHardwareProviderFactory {
public:
    explicit WindowsRenderHardwareProviderFactory(DiContainer* diContainer);
    IRenderHardwareProvider* CreateRenderHardwareProvider(RenderingApi renderingApi, bool* initializationSucceeded) override;
private:
    DiContainer* m_diContainer;
};