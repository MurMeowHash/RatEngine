#include "../Public/EngineDependencyContext.h"
#include "Installers/DebugModuleInstaller.h"
#include "Installers/EventBusModuleInstaller.h"

void EngineDependencyContext::ConstructCompositionRoot() {
    DebugModuleInstaller::InstallDependencies(m_diContainer);
    EventBusModuleInstaller::InstallDependencies(m_diContainer);
}
