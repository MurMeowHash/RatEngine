#include "../Public/ConcurrencyModuleInstaller.h"
#include "IConcurrencyFactory.h"
#include "WorldThreadWrapper.h"
#include "PlatformInteractors/IPlatformInteractor.h"
#include "ProjectSettings/ProjectSettings.h"

#if defined(__WIN32)
#include "WindowsConcurrencyFactory.h"
#else
#include "MockPlatformThreadFactory.h"
#endif

void ConcurrencyModuleInstaller::InstallBindings(DiContainer *diContainer) const {
#if defined(__WIN32)
    diContainer->Bind<IConcurrencyFactory>(ClientBinding([](){return new WindowsConcurrencyFactory();}));
#else
    diContainer->Bind<IPlatformThreadFactory>(ClientBinding([](){return new MockPlatformThreadFactory();}));
#endif

    diContainer->Bind<WorldThreadWrapper>(ClientBinding([diContainer](){
        return new WorldThreadWrapper(diContainer->Resolve<IPlatformInteractor>(), diContainer->Resolve<ProjectSettings>());
    }, std::vector<std::type_index>{typeid(IPlatformInteractor), typeid(ProjectSettings)}));
}