#pragma once

#include "RenderingApi.h"

class IRenderProviderInitializer {
public:
    virtual bool InitializeRenderProvider(RenderingApi renderingApi) = 0;
    virtual bool InitializeRenderProvider() = 0;
    virtual ~IRenderProviderInitializer() = default;
};