#pragma once

#include "IPlatformThread.h"

class IPlatformThreadFactory {
public:
    virtual IPlatformThread* CreatePlatformThread(IDelegate<>* executeAction, size_t stackSize, ThreadCreationFlags flags) = 0;
    virtual ~IPlatformThreadFactory() = default;
};