#include "../Public/RenderProviderModuleInstaller.h"
#include "RenderProviderAccessor.h"
#include "IRenderProviderFactory.h"
#include "IRenderProviderInitializer.h"
#include "RenderProviderInitializer.h"
#include "IRenderPriorityQueue.h"

#if defined(__WIN32)
#include "WindowsRenderProviderFactory.h"
#include "WindowsRenderPriorityQueue.h"
#else
#include "MockRenderProviderFactory.h"
#include "MockRenderPriorityQueue.h"
#endif

void RenderProviderModuleInstaller::InstallBindings(DiContainer &diContainer) const {
    diContainer.Bind<RenderProviderAccessor>(ClientBinding([](){return new RenderProviderAccessor();}));
#if defined(__WIN32)
    diContainer.Bind<IRenderProviderFactory>(ClientBinding([&diContainer](){
        return new WindowsRenderProviderFactory(diContainer);
    }, std::vector<std::type_index>{ }));

    diContainer.Bind<IRenderPriorityQueue>(ClientBinding([](){return new WindowsRenderPriorityQueue();}));
#else
    diContainer.Bind<IRenderProviderFactory>(ClientBinding([](){return new MockRenderProviderFactory();}));
    diContainer.Bind<IRenderPriorityQueue>(ClientBinding([](){return new MockRenderPriorityQueue();}));
#endif

    diContainer.Bind<IRenderProviderInitializer>(ClientBinding([&diContainer](){
        return new RenderProviderInitializer(diContainer.Resolve<IRenderProviderFactory>(),
                diContainer.Resolve<RenderProviderAccessor>(), diContainer.Resolve<IRenderPriorityQueue>());
    }, std::vector<std::type_index>{ typeid(IRenderProviderFactory), typeid(RenderProviderAccessor), typeid(IRenderPriorityQueue) }));
}