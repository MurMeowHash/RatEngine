#include "../Public/MockConcurrencyFactory.h"
#include "MockPlatformThread.h"
#include "MockMutex.h"

IPlatformThread * MockConcurrencyFactory::CreatePlatformThread(IDelegate<> *executeAction, size_t stackSize, ThreadCreationFlags flags) {
    return new MockPlatformThread();
}

IMutex *MockConcurrencyFactory::CreatePlatformMutex(bool initiallyLocked) {
    return new MockMutex();
}