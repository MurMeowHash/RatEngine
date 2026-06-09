#include "../Public/RenderHardwareDependencyContext.h"
#include "RenderHardwareModuleInstaller.h"

RenderHardwareDependencyContext::RenderHardwareDependencyContext(const DiContainer *parentContainer)
: DependencyContextBase(parentContainer) { }

void RenderHardwareDependencyContext::ConstructCompositionRoot() {
    RenderHardwareModuleInstaller::InstallDependencies(m_diContainer);
    ConstructRenderHardwareDependencies();
}