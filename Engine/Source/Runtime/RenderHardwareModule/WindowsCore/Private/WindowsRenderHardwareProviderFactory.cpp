#include "../Public/WindowsRenderHardwareProviderFactory.h"
#include "VulkanRenderHardwareProvider.h"
#include "BuildSettings/BuildSettings.h"
#include <stdexcept>

WindowsRenderHardwareProviderFactory::WindowsRenderHardwareProviderFactory(DiContainer* diContainer)
: m_diContainer(diContainer) { }

IRenderHardwareProvider* WindowsRenderHardwareProviderFactory::CreateRenderHardwareProvider(RenderingApi renderingApi, bool* initializationSucceeded) {
    switch (renderingApi) {
        case RenderingApi::Vulkan:
            {
                IRenderHardwareProvider* renderHardwareProvider = m_diContainer->Instantiate<VulkanRenderHardwareProvider>()
                    .WithArguments<IVulkanInstanceFactory, IVulkanDeviceFactory, IVulkanDeviceProvider, BuildSettings>();

                bool initialized = renderHardwareProvider->Initialize();
                if (initializationSucceeded)
                    *initializationSucceeded = initialized;

                return renderHardwareProvider;
            }
        default:
            throw std::invalid_argument(StringFormatter("Rendering Api with type ", static_cast<uint32_t>(renderingApi), " is not supported on current platform"));
    }
}