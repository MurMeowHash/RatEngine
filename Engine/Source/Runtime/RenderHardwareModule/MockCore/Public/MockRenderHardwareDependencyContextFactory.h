#pragma once

#include "IRenderHardwareDependencyContextFactory.h"

class MockRenderHardwareDependencyContextFactory : public IRenderHardwareDependencyContextFactory {
public:
    RenderHardwareDependencyContext* CreateRenderHardwareDependencyContext(RenderingApi renderingApi, DiContainer* parentDiContainer) override;
};