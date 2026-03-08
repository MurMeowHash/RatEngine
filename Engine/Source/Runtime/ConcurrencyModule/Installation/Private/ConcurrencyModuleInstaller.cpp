#include "../Public/ConcurrencyModuleInstaller.h"
#include "IPlatformThreadFactory.h"

#if defined(__WIN32)
#include "WindowsPlatformThreadFactory.h"
#else
#include "MockPlatformThreadFactory.h"
#endif

void ConcurrencyModuleInstaller::InstallBindings(DiContainer *diContainer) const {
#if defined(__WIN32)
    diContainer->Bind<IPlatformThreadFactory>(ClientBinding([](){return new WindowsPlatformThreadFactory();}));
#else
    diContainer->Bind<IPlatformThreadFactory>(ClientBinding([](){return new MockPlatformThreadFactory();}));
#endif
}