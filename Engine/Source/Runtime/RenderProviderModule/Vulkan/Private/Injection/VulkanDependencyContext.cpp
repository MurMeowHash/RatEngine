#include "Injection/VulkanDependencyContext.h"
#include "Injection/Installers/VulkanInstaller.h"

void VulkanDependencyContext::ConstructCompositionRoot() {
    VulkanInstaller::InstallDependencies(m_diContainer);
}