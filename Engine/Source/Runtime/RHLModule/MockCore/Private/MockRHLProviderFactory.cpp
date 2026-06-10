#include "../Public/MockRHLProviderFactory.h"
#include "MockRHLProvider.h"

IRHLProvider* MockRHLProviderFactory::CreateRHLProvider(RenderingApi renderingApi, bool* initializationSucceeded) {
    IRHLProvider* rhlProvider = new MockRHLProvider();
    if (initializationSucceeded)
        *initializationSucceeded = false;

    return rhlProvider;
}