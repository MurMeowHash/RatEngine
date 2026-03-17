#include "../Public/CoreModuleInstaller.h"
#include "ProjectSettings/ProjectSettings.h"
#include "ProjectSettings/IProjectSettingsInitializer.h"
#include "ProjectSettings/HardCodedProjectSettingsInitializer.h"
#include "Application/Application.h"
#include "BuildSettings/BuildSettings.h"
#include "Application/IApplicationInitializer.h"
#include "Application/HardCodedApplicationInitializer.h"
#include "BuildSettings/IBuildSettingsInitializer.h"
#include "BuildSettings/HardCodedBuildSettingsInitializer.h"

#if defined(__WIN32)
#include "PlatformInteractors/WindowsPlatformInteractor.h"
#else
#include "PlatformInteractors/MockPlatformInteractor.h"
#endif

void CoreModuleInstaller::InstallBindings(DiContainer* diContainer) const {
    diContainer->Bind<ProjectSettings>(ClientBinding([](){return new ProjectSettings();}));
    diContainer->Bind<IProjectSettingsInitializer>(ClientBinding([diContainer]() {
        return new HardCodedProjectSettingsInitializer(diContainer->Resolve<ProjectSettings>());
    }, std::vector<std::type_index>{typeid(ProjectSettings)}));
    diContainer->Bind<Application>(ClientBinding([](){return new Application();}));
    diContainer->Bind<BuildSettings>(ClientBinding([](){return new BuildSettings();}));
    diContainer->Bind<IApplicationInitializer>(ClientBinding([diContainer](){
        return new HardCodedApplicationInitializer(diContainer->Resolve<Application>());
    }, std::vector<std::type_index> { typeid(Application) }));
    diContainer->Bind<IBuildSettingsInitializer>(ClientBinding([diContainer](){
        return new HardCodedBuildSettingsInitializer(diContainer->Resolve<BuildSettings>());
    }, std::vector<std::type_index> { typeid(BuildSettings) }));

#if defined(__WIN32)
    diContainer->Bind<IPlatformInteractor>(ClientBinding([](){return new WindowsPlatformInteractor();}));
#else
    diContainer->Bind<IPlatformInteractor>(ClientBinding([](){return new MockPlatformInteractor();}));
#endif
}