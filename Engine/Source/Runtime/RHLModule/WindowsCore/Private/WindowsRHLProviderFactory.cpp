#include "../Public/WindowsRHLProviderFactory.h"
#include "VulkanRHLProvider.h"
#include "BuildSettings/BuildSettings.h"
#include <stdexcept>

WindowsRHLProviderFactory::WindowsRHLProviderFactory(DiContainer* diContainer)
: m_diContainer(diContainer) { }

IRHLProvider* WindowsRHLProviderFactory::CreateRHLProvider(RenderingApi renderingApi, bool* initializationSucceeded) {
    switch (renderingApi) {
        case RenderingApi::Vulkan:
            {
                IRHLProvider* rhlProvider = m_diContainer->Instantiate<VulkanRHLProvider>()
                    .WithArguments<IVulkanInstanceFactory, IVulkanDeviceFactory, IVulkanDeviceProvider, BuildSettings, RatVulkanMapperInitializer>();

                bool initialized = rhlProvider->Initialize();
                if (initializationSucceeded)
                    *initializationSucceeded = initialized;

                return rhlProvider;
            }
        default:
            throw std::invalid_argument(StringFormatter("Rendering Api with type ", static_cast<uint32_t>(renderingApi), " is not supported on current platform"));
    }
}