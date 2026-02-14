#include "../Public/Injection/Installers/VulkanInstaller.h"
#include "Extensions/IVulkanExtensionsAssembler.h"
#include "Extensions/IVulkanPlatformExtensionsProvider.h"
#include "Extensions/VulkanExtensionsAssembler.h"
#include "ValidationLayers/IVulkanLayersValidator.h"
#include "ValidationLayers/VulkanLayersValidator.h"
#include "ValidationLayers/IVulkanDebugAdapter.h"
#include "ValidationLayers/VulkanDebugAdapter.h"
#include "ILogger.h"

#if defined(__WIN64)
#include "Extensions/VulkanWindowsExtensionsProvider.h"
#else
#include "Extensions/VulkanMockExtensionsProvider.h"
#endif

void VulkanInstaller::InstallBindings(DiContainer* diContainer) const {
    diContainer->Bind<IVulkanExtensionsAssembler>(ClientBinding([diContainer](){
        return new VulkanExtensionsAssembler(diContainer->Resolve<IVulkanPlatformExtensionsProvider>());
    }, std::vector<std::type_index>{typeid(IVulkanPlatformExtensionsProvider)}));
    diContainer->Bind<IVulkanLayersValidator>(ClientBinding([](){return new VulkanLayersValidator();}));
    diContainer->Bind<IVulkanDebugAdapter>(ClientBinding([diContainer](){
        return new VulkanDebugAdapter(diContainer->Resolve<ILogger>());
    }, std::vector<std::type_index> { typeid(ILogger) }));

#if defined(__WIN64)
    diContainer->Bind<IVulkanPlatformExtensionsProvider>(ClientBinding([](){return new VulkanWindowsExtensionsProvider();}));
#else
    diContainer->Bind<IVulkanPlatformExtensionsProvider>(ClientBinding([](){return new VulkanMockExtensionsProvider();}));
#endif
}