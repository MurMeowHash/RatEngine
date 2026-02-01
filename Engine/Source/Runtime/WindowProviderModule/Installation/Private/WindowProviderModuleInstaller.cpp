#include "../Public/WindowProviderModuleInstaller.h"
#include "IWindowProvider.h"

#if defined(__WIN64) || defined(__APPLE__) || defined(__linux__)
#include "GlfwProvider/GlfwWindowProvider.h"
#else
#include "MockWindowProvider"
#endif

void WindowProviderModuleInstaller::InstallBindings(DiContainer &diContainer) const {
#if defined(__WIN64) || defined(__APPLE__) || defined(__linux__)
    diContainer.Bind<IWindowProvider>(ClientBinding([](){return new GlfwWindowProvider();}));
#else
    diContainer.Bind<IWindowProvider>(ClientBinding([](){return new MockWindowProvider();}));
#endif
}