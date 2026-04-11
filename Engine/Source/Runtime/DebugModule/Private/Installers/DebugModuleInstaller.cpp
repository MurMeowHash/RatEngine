#include "../../Public/Installers/DebugModuleInstaller.h"
#include "ILogger.h"
#include "SynchronousLogger.h"
#include "IConcurrencyFactory.h"

void DebugModuleInstaller::InstallBindings(DiContainer* diContainer) const {
    diContainer->Bind<SynchronousLogger>().To<ILogger>().WithArguments<IConcurrencyFactory>();
}