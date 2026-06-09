#include "../Public/RenderHardwareModuleInstaller.h"

#if defined(__WIN32)
#include "WindowsRenderHardwareProviderFactory.h"
#else
#include "MockRenderHardwareProviderFactory.h"
#endif

void RenderHardwareModuleInstaller::InstallBindings(DiContainer *diContainer) const {
#if defined(__WIN32)
    diContainer->Bind<WindowsRenderHardwareProviderFactory>().To<IRenderHardwareProviderFactory>().WithArguments<DiContainer>();
#else
    diContainer->Bind<MockRenderHardwareProviderFactory>().To<IRenderHardwareProviderFactory>().WithArguments<>();
#endif
}
