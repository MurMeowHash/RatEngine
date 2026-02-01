#include "../Public/CoreModuleInstaller.h"
#include "ProjectSettings/ProjectSettings.h"
#include "ProjectSettings/IProjectSettingsInitializer.h"
#include "ProjectSettings/HardCodedProjectSettingsInitializer.h"

#if defined(__WIN32)
#include "PlatformInteractors/WindowsPlatformInteractor.h"
#else
#include "PlatformInteractors/MockPlatformInteractor.h"
#endif

void CoreModuleInstaller::InstallBindings(DiContainer &diContainer) const {
    diContainer.Bind<ProjectSettings>(ClientBinding([](){return new ProjectSettings();}));
    diContainer.Bind<IProjectSettingsInitializer>(ClientBinding([&diContainer]() {
        return new HardCodedProjectSettingsInitializer(diContainer.Resolve<ProjectSettings>());
    }, std::vector<std::type_index>{typeid(ProjectSettings)}));

#if defined(__WIN32)
    diContainer.Bind<IPlatformInteractor>(ClientBinding([](){return new WindowsPlatformInteractor();}));
#else
    diContainer.Bind<IPlatformInteractor>(ClientBinding([](){return new MockPlatformInteractor();}));
#endif
}