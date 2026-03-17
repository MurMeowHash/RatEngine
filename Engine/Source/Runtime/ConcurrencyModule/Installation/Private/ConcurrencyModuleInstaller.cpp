#include "../Public/ConcurrencyModuleInstaller.h"
#include "IConcurrencyFactory.h"

#if defined(__WIN32)
#include "WindowsConcurrencyFactory.h"
#else
#include "MockPlatformThreadFactory.h"
#endif

void ConcurrencyModuleInstaller::InstallBindings(DiContainer *diContainer) const {
#if defined(__WIN32)
    diContainer->Bind<IConcurrencyFactory>(ClientBinding([](){return new WindowsConcurrencyFactory();}));
#else
    diContainer->Bind<IPlatformThreadFactory>(ClientBinding([](){return new MockPlatformThreadFactory();}));
#endif
}