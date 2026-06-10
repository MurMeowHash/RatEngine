#pragma once

#include "RHLDependencyContext.h"

enum class RenderingApi;
class DiContainer;

class IRHLDependencyContextFactory {
public:
    virtual RHLDependencyContext* CreateRHLDependencyContext(RenderingApi renderingApi, DiContainer* parentDiContainer) = 0;
    virtual ~IRHLDependencyContextFactory() = default;
};
