#include "../Public/ConcurrencyModuleInstaller.h"
#include "IConcurrencyFactory.h"
#include "ThreadStorage.h"
#include "CommandThreadStorage.h"
#include "ThreadSearchService.h"
#include "Runner/ThreadRunner.h"

#if defined(__WIN32)
#include "WindowsConcurrencyFactory.h"
#else
#include "MockConcurrencyFactory.h"
#endif

void ConcurrencyModuleInstaller::InstallBindings(DiContainer *diContainer) const {
#if defined(__WIN32)
    diContainer->Bind<WindowsConcurrencyFactory>().To<IConcurrencyFactory>().WithArguments();
#else
    diContainer->Bind<MockConcurrencyFactory>().To<IConcurrencyFactory>().WithArguments();
#endif

    diContainer->Bind<ThreadStorage>().To<ThreadStorage>().WithArguments<IConcurrencyFactory>();
    diContainer->Bind<CommandThreadStorage>().To<CommandThreadStorage>().WithArguments<IConcurrencyFactory>();
    diContainer->Bind<ThreadSearchService>().To<ThreadSearchService>().WithArguments<ThreadStorage, CommandThreadStorage>();
    diContainer->Bind<ThreadRunner>().To<ThreadRunner>().WithArguments<DiContainer, CommandThreadStorage, ThreadStorage>();
}