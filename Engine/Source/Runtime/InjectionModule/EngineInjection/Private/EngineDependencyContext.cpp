#include "../Public/EngineDependencyContext.h"
#include "Installers/DebugModuleInstaller.h"
#include "Installers/EventBusModuleInstaller.h"
#include "CoreModuleInstaller.h"
#include "WindowProviderModuleInstaller.h"
#include "RenderProviderModuleInstaller.h"

EngineDependencyContext::EngineDependencyContext(const DiContainer *parentContainer)
: DependencyContextBase(parentContainer) { }

void EngineDependencyContext::ConstructCompositionRoot() {
    DebugModuleInstaller::InstallDependencies(m_diContainer);
    EventBusModuleInstaller::InstallDependencies(m_diContainer);
    CoreModuleInstaller::InstallDependencies(m_diContainer);
    WindowProviderModuleInstaller::InstallDependencies(m_diContainer);
    RenderProviderModuleInstaller::InstallDependencies(m_diContainer);
}
