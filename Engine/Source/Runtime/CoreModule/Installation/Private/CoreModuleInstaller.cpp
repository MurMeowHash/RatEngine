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
    diContainer->Bind<ProjectSettings>().To<ProjectSettings>().WithArguments<>();
    diContainer->Bind<HardCodedProjectSettingsInitializer>().To<IProjectSettingsInitializer>().WithArguments<ProjectSettings>();
    diContainer->Bind<Application>().To<Application>().WithArguments<>();
    diContainer->Bind<BuildSettings>().To<BuildSettings>().WithArguments<>();
    diContainer->Bind<HardCodedApplicationInitializer>().To<IApplicationInitializer>().WithArguments<Application>();
    diContainer->Bind<HardCodedBuildSettingsInitializer>().To<IBuildSettingsInitializer>().WithArguments<BuildSettings>();

#if defined(__WIN32)
    diContainer->Bind<WindowsPlatformInteractor>().To<IPlatformInteractor>().WithArguments<>();
#else
    diContainer->Bind<MockPlatformInteractor>().To<IPlatformInteractor>().WithArguments<>();
#endif
}