#pragma once

#include "IRHLProvider.h"
#include "RenderingApi.h"

class IRHLProviderFactory {
public:
    virtual IRHLProvider* CreateRHLProvider(RenderingApi renderingApi, bool* initializationSucceeded) = 0;
    virtual ~IRHLProviderFactory() = default;
};