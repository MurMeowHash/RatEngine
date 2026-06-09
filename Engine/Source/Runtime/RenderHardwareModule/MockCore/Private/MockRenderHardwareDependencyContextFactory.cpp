#include "../Public/MockRenderHardwareDependencyContextFactory.h"
#include "RenderingApi.h"
#include "MockRenderHardwareDependencyContext.h"

RenderHardwareDependencyContext* MockRenderHardwareDependencyContextFactory::CreateRenderHardwareDependencyContext(RenderingApi renderingApi, DiContainer* parentDiContainer) {
    return new MockRenderHardwareDependencyContext(parentDiContainer);
}