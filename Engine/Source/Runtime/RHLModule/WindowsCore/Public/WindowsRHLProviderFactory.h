#pragma once

#include "IRHLProviderFactory.h"
#include "DiContainer.h"

class WindowsRHLProviderFactory : public IRHLProviderFactory {
public:
    explicit WindowsRHLProviderFactory(DiContainer* diContainer);
    IRHLProvider* CreateRHLProvider(RenderingApi renderingApi, bool* initializationSucceeded) override;
private:
    DiContainer* m_diContainer;
};