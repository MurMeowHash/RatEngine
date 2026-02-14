#include "Injection/VulkanDependencyContext.h"
#include "Injection/Installers/VulkanInstaller.h"

VulkanDependencyContext::VulkanDependencyContext(const DiContainer *parentContainer)
: DependencyContextBase(parentContainer) {}

void VulkanDependencyContext::ConstructCompositionRoot() {
    VulkanInstaller::InstallDependencies(m_diContainer);
}
