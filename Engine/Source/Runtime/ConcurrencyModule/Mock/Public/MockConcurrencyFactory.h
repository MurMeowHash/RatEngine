#pragma once

#include "IConcurrencyFactory.h"

class MockConcurrencyFactory : public IConcurrencyFactory {
public:
    IPlatformThread* CreatePlatformThread(IDelegate<> *executeAction, size_t stackSize, ThreadCreationFlags flags) override;
    IMutex* CreatePlatformMutex() override;
    IFence* CreatePlatformFence(bool invokeMemoryBarrier) override;
    ISemaphore* CreatePlatformSemaphore(int32_t initialUsages, int32_t maxUsages) override;
};