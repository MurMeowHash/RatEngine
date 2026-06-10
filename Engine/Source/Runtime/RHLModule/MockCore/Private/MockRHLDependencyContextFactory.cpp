#include "../Public/MockRHLDependencyContextFactory.h"
#include "RenderingApi.h"
#include "MockRHLDependencyContext.h"

RHLDependencyContext* MockRHLDependencyContextFactory::CreateRHLDependencyContext(RenderingApi renderingApi, DiContainer* parentDiContainer) {
    return new MockRHLDependencyContext(parentDiContainer);
}