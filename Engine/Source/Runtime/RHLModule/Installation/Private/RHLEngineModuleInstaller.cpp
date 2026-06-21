#include "../Public/RHLEngineModuleInstaller.h"
#include "RHLRuntimeData.h"
#include "IRHLProviderFactory.h"
#include "Configurations/RenderApi/RenderApiConfiguration.h"
#include "../Public/IRHLDependencyContextFactory.h"

#if defined(__WIN32)
#include "WindowsRHLDependencyContextFactory.h"
#else
#include "MockRHLDependencyContextFactory.h"
#endif

void RHLEngineModuleInstaller::InstallBindings(DiContainer* diContainer) const {
    diContainer->Bind<RHLRuntimeData>().To<RHLRuntimeData>().WithArguments<>();

#if defined(__WIN32)
    diContainer->Bind<WindowsRHLDependencyContextFactory>().To<IRHLDependencyContextFactory>().WithArguments<>();
#else
    diContainer->Bind<MockRHLDependencyContextFactory>().To<IRHLDependencyContextFactory>().WithArguments<>();
#endif

    diContainer->Bind<RenderApiConfiguration>().To<RenderApiConfiguration>().WithArguments<>();
}