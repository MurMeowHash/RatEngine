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
    diContainer->Bind<IWindowProvider>(ClientBinding([diContainer](){
        return new GlfwWindowProvider(diContainer->Resolve<IPlatformInteractor>());
    }, std::vector<std::type_index>{typeid(IPlatformInteractor)}));
#else
    diContainer->Bind<IWindowProvider>(ClientBinding([](){return new MockWindowProvider();}));
#endif
}