#include "../Public/MockConcurrencyFactory.h"
#include "MockPlatformThread.h"
#include "../Public/SynchronizationPrimitives/MockMutex.h"
#include "SynchronizationPrimitives/MockFence.h"
#include "SynchronizationPrimitives/MockSemaphore.h"

IPlatformThread * MockConcurrencyFactory::CreatePlatformThread(IDelegate<> *executeAction, size_t stackSize, ThreadCreationFlags flags) {
    return new MockPlatformThread();
}

IMutex *MockConcurrencyFactory::CreatePlatformMutex() {
    return new MockMutex();
}

IFence * MockConcurrencyFactory::CreatePlatformFence(bool invokeMemoryBarrier) {
    return new MockFence();
}

ISemaphore * MockConcurrencyFactory::CreatePlatformSemaphore(int32_t initialUsages, int32_t maxUsages) {
    return new MockSemaphore();
}