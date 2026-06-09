#include "../Public/RenderHardwareEngineModuleInstaller.h"
#include "RenderHardwareRuntimeData.h"
#include "IRenderHardwareProviderFactory.h"
#include "Configurations/RenderApi/RenderApiConfiguration.h"
#include "../Public/IRenderHardwareDependencyContextFactory.h"

#if defined(__WIN32)
#include "WindowsRenderHardwareDependencyContextFactory.h"
#else
#include "MockRenderHardwareDependencyContextFactory.h"
#endif

void RenderHardwareEngineModuleInstaller::InstallBindings(DiContainer* diContainer) const {
    diContainer->Bind<RenderHardwareRuntimeData>().To<RenderHardwareRuntimeData>().WithArguments<>();

#if defined(__WIN32)
    diContainer->Bind<WindowsRenderHardwareDependencyContextFactory>().To<IRenderHardwareDependencyContextFactory>().WithArguments<>();
#else
    diContainer->Bind<MockRenderHardwareDependencyContextFactory>().To<IRenderHardwareDependencyContextFactory>().WithArguments<>();
#endif

    diContainer->Bind<RenderApiConfiguration>().To<RenderApiConfiguration>().WithArguments<>();
}