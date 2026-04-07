#pragma once

#include "IPlatformThread.h"
#include "SynchronizationPrimitives/IMutex.h"
#include "SynchronizationPrimitives/IFence.h"
#include "SynchronizationPrimitives/ISemaphore.h"

class IConcurrencyFactory {
public:
    virtual IPlatformThread* CreatePlatformThread(IDelegate<>* executeAction, size_t stackSize, ThreadCreationFlags flags) = 0;
    virtual IMutex* CreatePlatformMutex() = 0;
    virtual IFence* CreatePlatformFence(bool invokeMemoryBarrier) = 0;
    virtual ISemaphore* CreatePlatformSemaphore(int32_t initialUsages, int32_t maxUsages) = 0;
    virtual ~IConcurrencyFactory() = default;
};