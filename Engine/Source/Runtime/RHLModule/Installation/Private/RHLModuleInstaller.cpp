#include "../Public/RHLModuleInstaller.h"

#if defined(__WIN32)
#include "WindowsRHLProviderFactory.h"
#else
#include "MockRHLProviderFactory.h"
#endif

void RHLModuleInstaller::InstallBindings(DiContainer *diContainer) const {
#if defined(__WIN32)
    diContainer->Bind<WindowsRHLProviderFactory>().To<IRHLProviderFactory>().WithArguments<DiContainer>();
#else
    diContainer->Bind<MockRHLProviderFactory>().To<IRHLProviderFactory>().WithArguments<>();
#endif
}
