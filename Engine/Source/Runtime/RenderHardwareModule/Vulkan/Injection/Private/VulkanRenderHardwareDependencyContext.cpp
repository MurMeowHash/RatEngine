#include "../Public/VulkanRenderHardwareDependencyContext.h"

#include "Installers/VulkanConfigurationsInstaller.h"
#include "Installers/VulkanHardwareInstaller.h"

VulkanRenderHardwareDependencyContext::VulkanRenderHardwareDependencyContext(const DiContainer *parentDiContainer)
: RenderHardwareDependencyContext(parentDiContainer) { }

void VulkanRenderHardwareDependencyContext::ConstructRenderHardwareDependencies() {
    VulkanHardwareInstaller::InstallDependencies(m_diContainer);
    VulkanConfigurationsInstaller::InstallDependencies(m_diContainer);
}