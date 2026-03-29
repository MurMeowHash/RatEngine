#pragma once

#include "IPlatformThread.h"
#include "SynchronizationPrimitives/IMutex.h"

class IConcurrencyFactory {
public:
    virtual IPlatformThread* CreatePlatformThread(IDelegate<>* executeAction, size_t stackSize, ThreadCreationFlags flags) = 0;
    virtual IMutex* CreatePlatformMutex() = 0;
    virtual ~IConcurrencyFactory() = default;
};