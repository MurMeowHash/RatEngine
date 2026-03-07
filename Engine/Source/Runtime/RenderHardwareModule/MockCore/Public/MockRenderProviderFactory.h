#pragma once

#include "IRenderProviderFactory.h"

class MockRenderProviderFactory : public IRenderProviderFactory {
public:
    std::unique_ptr<IRenderProvider> CreateRenderProvider(RenderingApi renderingApi) override;
};