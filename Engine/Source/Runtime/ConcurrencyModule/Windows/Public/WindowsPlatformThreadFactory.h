#pragma once

#include "IPlatformThreadFactory.h"

class WindowsPlatformThreadFactory : public IPlatformThreadFactory {
public:
    IPlatformThread* CreatePlatformThread(IDelegate<> *executeAction, size_t stackSize, ThreadCreationFlags flags) override;
};