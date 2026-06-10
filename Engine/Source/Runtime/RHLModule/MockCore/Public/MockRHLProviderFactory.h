#pragma once

#include "IRHLProviderFactory.h"

class MockRHLProviderFactory : public IRHLProviderFactory {
public:
    IRHLProvider* CreateRHLProvider(RenderingApi renderingApi, bool* initializationSucceeded) override;
};