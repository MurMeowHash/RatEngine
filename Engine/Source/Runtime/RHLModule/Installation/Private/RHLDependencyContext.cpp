#include "../Public/RHLDependencyContext.h"
#include "RHLModuleInstaller.h"

RHLDependencyContext::RHLDependencyContext(const DiContainer *parentContainer)
: DependencyContextBase(parentContainer) { }

void RHLDependencyContext::ConstructCompositionRoot() {
    RHLModuleInstaller::InstallDependencies(m_diContainer);
    ConstructRHLDependencies();
}