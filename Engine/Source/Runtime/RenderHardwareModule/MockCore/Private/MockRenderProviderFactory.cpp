#include "../Public/MockRenderProviderFactory.h"

std::unique_ptr<IRenderProvider> MockRenderProviderFactory::CreateRenderProvider(RenderingApi renderingApi) {
    return nullptr;
}