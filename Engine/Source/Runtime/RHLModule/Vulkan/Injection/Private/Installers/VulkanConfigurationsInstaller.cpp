#include "../../Public/Installers/VulkanConfigurationsInstaller.h"
#include "Configurations/Device/VulkanAllocationConfiguration.h"
#include "Configurations/Device/VulkanDeviceConfiguration.h"
#include "Configurations/Instance/VulkanInstanceConfiguration.h"
#include "Configurations/Resources/VulkanResourcesConfiguration.h"

#if defined(__WIN64)
#include "Configurations/Extensions/WindowsVulkanExtensionsConfiguration.h"
#else
#include "Configurations/Extensions/MockVulkanExtensionsConfiguration.h"
#endif


void VulkanConfigurationsInstaller::InstallBindings(DiContainer *diContainer) const {
#if defined(__WIN64)
    diContainer->Bind<WindowsVulkanExtensionsConfiguration>().To<VulkanExtensionsConfiguration>().WithArguments<>();
#else
    diContainer->Bind<MockVulkanExtensionsConfiguration>().To<VulkanExtensionsConfiguration>().WithArguments<>();
#endif

    diContainer->Bind<VulkanAllocationConfiguration>().To<VulkanAllocationConfiguration>().WithArguments<>();
    diContainer->Bind<VulkanDeviceConfiguration>().To<VulkanDeviceConfiguration>().WithArguments<>();
    diContainer->Bind<VulkanInstanceConfiguration>().To<VulkanInstanceConfiguration>().WithArguments<>();
    diContainer->Bind<VulkanResourcesConfiguration>().To<VulkanResourcesConfiguration>().WithArguments<>();
}