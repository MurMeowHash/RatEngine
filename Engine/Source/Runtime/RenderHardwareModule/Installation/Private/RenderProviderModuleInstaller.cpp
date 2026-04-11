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

void RenderProviderModuleInstaller::InstallBindings(DiContainer* diContainer) const {
    diContainer->Bind<RenderProviderAccessor>().To<RenderProviderAccessor>().WithArguments<>();
#if defined(__WIN32)
    diContainer->Bind<WindowsRenderProviderFactory>().To<IRenderProviderFactory>().WithArguments<DiContainer>();
    diContainer->Bind<WindowsRenderPriorityQueue>().To<IRenderPriorityQueue>().WithArguments<>();
#else
    diContainer->Bind<MockRenderProviderFactory>().To<IRenderProviderFactory>().WithArguments<>();
    diContainer->Bind<MockRenderPriorityQueue>().To<IRenderPriorityQueue>().WithArguments<>();
#endif

    diContainer->Bind<RenderProviderInitializer>().To<IRenderProviderInitializer>().WithArguments<IRenderProviderFactory, RenderProviderAccessor, IRenderPriorityQueue>();
}