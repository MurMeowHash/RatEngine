#include "../Public/MockRenderHardwareProviderFactory.h"
#include "MockRenderHardwareProvider.h"

IRenderHardwareProvider* MockRenderHardwareProviderFactory::CreateRenderHardwareProvider(RenderingApi renderingApi, bool* initializationSucceeded) {
    IRenderHardwareProvider* renderHardwareProvider = new MockRenderHardwareProvider();
    if (initializationSucceeded)
        *initializationSucceeded = false;

    return renderHardwareProvider;
}