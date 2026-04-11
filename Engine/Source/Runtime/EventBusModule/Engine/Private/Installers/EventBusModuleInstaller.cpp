#include "../../Public/Installers/EventBusModuleInstaller.h"
#include "EngineCoreEventBus.h"

void EventBusModuleInstaller::InstallBindings(DiContainer* diContainer) const {
    diContainer->Bind<EngineCoreEventBus>().To<EngineCoreEventBus>().WithArguments<IConcurrencyFactory>();
}
