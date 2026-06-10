#include "../Public/VulkanRHLDependencyContext.h"

#include "Installers/VulkanConfigurationsInstaller.h"
#include "Installers/VulkanHardwareInstaller.h"

VulkanRHLDependencyContext::VulkanRHLDependencyContext(const DiContainer *parentDiContainer)
: RHLDependencyContext(parentDiContainer) { }

void VulkanRHLDependencyContext::ConstructRHLDependencies() {
    VulkanHardwareInstaller::InstallDependencies(m_diContainer);
    VulkanConfigurationsInstaller::InstallDependencies(m_diContainer);
}