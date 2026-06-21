#pragma once

#include "IRHLDependencyContextFactory.h"

class WindowsRHLDependencyContextFactory : public IRHLDependencyContextFactory {
public:
    RHLDependencyContext* CreateRHLDependencyContext(RenderingApi renderingApi, DiContainer* parentDiContainer) override;
};
