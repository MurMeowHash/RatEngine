#include "../Public/Installers/VulkanHardwareInstaller.h"
#include "ValidationLayers/IVulkanLayersValidator.h"
#include "ValidationLayers/VulkanLayersValidator.h"
#include "ValidationLayers/IVulkanDebugAdapter.h"
#include "ValidationLayers/VulkanDebugAdapter.h"
#include "ILogger.h"
#include "IVulkanDeviceProvider.h"
#include "VulkanDeviceProvider.h"
#include "Features/IVulkanDeviceFeaturesAssembler.h"
#include "Features/VulkanDeviceFeaturesAssembler.h"
#include "IVulkanDeviceFactory.h"
#include "VulkanDeviceFactory.h"
#include "Memory/VulkanDeviceMemoryProviderFactory.h"
#include "Extensions/IVulkanExtensionsValidator.h"
#include "Extensions/VulkanExtensionsValidator.h"
#include "Instance/VulkanInstanceFactory.h"
#include "PlatformInteractors/IPlatformInteractor.h"

void VulkanHardwareInstaller::InstallBindings(DiContainer* diContainer) const {
    diContainer->Bind<VulkanLayersValidator>().To<IVulkanLayersValidator>().WithArguments<>();
    diContainer->Bind<VulkanDebugAdapter>().To<IVulkanDebugAdapter>().WithArguments<ILogger>();
    diContainer->Bind<VulkanDeviceProvider>().To<IVulkanDeviceProvider>().WithArguments<>();
    diContainer->Bind<VulkanDeviceFeaturesAssembler>().To<IVulkanDeviceFeaturesAssembler>().WithArguments<>();
    diContainer->Bind<VulkanDeviceFactory>().To<IVulkanDeviceFactory>().WithArguments<DiContainer, VulkanDeviceConfiguration, VulkanExtensionsConfiguration>();
    diContainer->Bind<VulkanDeviceMemoryProviderFactory>().To<IVulkanDeviceMemoryProviderFactory>().WithArguments<VulkanAllocationConfiguration, IPlatformInteractor>();
    diContainer->Bind<VulkanExtensionsValidator>().To<IVulkanExtensionsValidator>().WithArguments<>();
    diContainer->Bind<VulkanInstanceFactory>().To<IVulkanInstanceFactory>().WithArguments<DiContainer, VulkanInstanceConfiguration,VulkanExtensionsConfiguration>();
}