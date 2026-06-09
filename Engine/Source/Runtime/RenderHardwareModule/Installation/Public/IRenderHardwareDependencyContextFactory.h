#pragma once

#include "RenderHardwareDependencyContext.h"

enum class RenderingApi;
class DiContainer;

class IRenderHardwareDependencyContextFactory {
public:
    virtual RenderHardwareDependencyContext* CreateRenderHardwareDependencyContext(RenderingApi renderingApi, DiContainer* parentDiContainer) = 0;
    virtual ~IRenderHardwareDependencyContextFactory() = default;
};
