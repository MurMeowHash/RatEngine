#include "../../Public/Installers/DebugModuleInstaller.h"
#include "ILogger.h"
#include "EngineLogger.h"

void DebugModuleInstaller::InstallBindings(DiContainer* diContainer) const {
    diContainer->Bind<ILogger>(ClientBinding([](){return new EngineLogger();}));
}