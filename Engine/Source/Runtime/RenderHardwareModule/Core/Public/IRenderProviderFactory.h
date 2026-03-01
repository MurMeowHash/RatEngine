#pragma once

#include "IRenderProvider.h"
#include "RenderingApi.h"
#include <memory>

class IRenderProviderFactory {
public:
    virtual std::unique_ptr<IRenderProvider> CreateRenderProvider(RenderingApi renderingApi) = 0;
    virtual ~IRenderProviderFactory() = default;
};