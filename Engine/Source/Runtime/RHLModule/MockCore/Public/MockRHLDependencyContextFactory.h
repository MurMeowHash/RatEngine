#pragma once

#include "IRHLDependencyContextFactory.h"

class MockRHLDependencyContextFactory : public IRHLDependencyContextFactory {
public:
    RHLDependencyContext* CreateRHLDependencyContext(RenderingApi renderingApi, DiContainer* parentDiContainer) override;
};