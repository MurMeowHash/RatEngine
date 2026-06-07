#include "../Public/Injection/Installers/VulkanInstaller.h"
#include "Extensions/IVulkanExtensionsAssembler.h"
#include "Extensions/IVulkanPlatformExtensionsProvider.h"
#include "Extensions/VulkanExtensionsAssembler.h"
#include "ValidationLayers/IVulkanLayersValidator.h"
#include "ValidationLayers/VulkanLayersValidator.h"
#include "ValidationLayers/IVulkanDebugAdapter.h"
#include "ValidationLayers/VulkanDebugAdapter.h"
#include "ILogger.h"
#include "IVulkanDeviceProvider.h"
#include "VulkanDeviceProvider.h"
#include "Features/IDeviceFeaturesAssembler.h"
#include "Features/DeviceFeaturesAssembler.h"
#include "IVulkanDeviceFactory.h"
#include "VulkanDeviceFactory.h"
#include "Memory/VulkanDeviceMemoryProviderFactory.h"

#if defined(__WIN64)
#include "Extensions/VulkanWindowsExtensionsProvider.h"
#else
#include "Extensions/VulkanMockExtensionsProvider.h"
#endif

void VulkanInstaller::InstallBindings(DiContainer* diContainer) const {
    diContainer->Bind<VulkanExtensionsAssembler>().To<IVulkanExtensionsAssembler>().WithArguments<IVulkanPlatformExtensionsProvider>();
    diContainer->Bind<VulkanLayersValidator>().To<IVulkanLayersValidator>().WithArguments<>();
    diContainer->Bind<VulkanDebugAdapter>().To<IVulkanDebugAdapter>().WithArguments<ILogger>();

#if defined(__WIN64)
    diContainer->Bind<VulkanWindowsExtensionsProvider>().To<IVulkanPlatformExtensionsProvider>().WithArguments<>();
#else
    diContainer->Bind<VulkanMockExtensionsProvider>().To<IVulkanPlatformExtensionsProvider>().WithArguments<>();
#endif
    diContainer->Bind<VulkanDeviceProvider>().To<IVulkanDeviceProvider>().WithArguments<>();
    diContainer->Bind<DeviceFeaturesAssembler>().To<IDeviceFeaturesAssembler>().WithArguments<>();

    diContainer->Bind<VulkanDeviceFactory>().To<IVulkanDeviceFactory>().WithArguments<IVulkanExtensionsAssembler, IDeviceFeaturesAssembler, DiContainer>();
    diContainer->Bind<VulkanDeviceMemoryProviderFactory>().To<IVulkanDeviceMemoryProviderFactory>().WithArguments<>();
}