#include "../Public/WindowProviderModuleInstaller.h"
#include "IWindowProvider.h"
#include "PlatformInteractors/IPlatformInteractor.h"

#if defined(__WIN64) || defined(__APPLE__) || defined(__linux__)
#include "GlfwProvider/GlfwWindowProvider.h"
#else
#include "MockWindowProvider"
#endif

void WindowProviderModuleInstaller::InstallBindings(DiContainer* diContainer) const {
#if defined(__WIN64) || defined(__APPLE__) || defined(__linux__)
    diContainer->Bind<GlfwWindowProvider>().To<IWindowProvider>().WithArguments<IPlatformInteractor>();
#else
    diContainer->Bind<MockWindowProvider>().To<IWindowProvider>().WithArguments<IPlatformInteractor>();
#endif
}