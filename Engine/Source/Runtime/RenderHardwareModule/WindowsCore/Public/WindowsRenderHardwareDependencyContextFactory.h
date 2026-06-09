#pragma once

#include "IRenderHardwareDependencyContextFactory.h"

class WindowsRenderHardwareDependencyContextFactory : public IRenderHardwareDependencyContextFactory {
public:
    RenderHardwareDependencyContext* CreateRenderHardwareDependencyContext(RenderingApi renderingApi, DiContainer* parentDiContainer) override;
};
