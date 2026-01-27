#include "EngineCoreEventBus.h"
#include "EngineDependencyContext.h"
#include "ILogger.h"
#include <iostream>

ILogger *g_logger;

class TestCoreEvent : public EngineCoreEvents::EngineCoreEvent {};

void Foo(const TestCoreEvent &testCoreEvent) {
    g_logger->PrintError("Test Core Event Invoked");
}

int main() {
    EngineDependencyContext engineDependencyContext;
    engineDependencyContext.OpenContext();

    const DiContainer &diContainer = engineDependencyContext.GetContainer();

    EngineCoreEventBus* engineCoreEventBus = diContainer.Resolve<EngineCoreEventBus>();
    g_logger = diContainer.Resolve<ILogger>();

    g_logger->SetOutputStream(&std::cout);

    StaticDelegate<const TestCoreEvent &>* fooDelegate = new StaticDelegate<const TestCoreEvent &>(Foo);
    engineCoreEventBus->Subscribe<TestCoreEvent>(fooDelegate);

    engineCoreEventBus->Publish(TestCoreEvent());

    engineCoreEventBus->UnSubscribe<TestCoreEvent>(fooDelegate);
    delete fooDelegate;
    engineDependencyContext.CloseContext();
    return 0;
}