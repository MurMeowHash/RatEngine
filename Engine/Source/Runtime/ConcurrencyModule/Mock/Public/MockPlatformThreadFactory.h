#pragma once

#include "IPlatformThreadFactory.h"

class MockPlatformThreadFactory : public IPlatformThreadFactory {
public:
    IPlatformThread* CreatePlatformThread(IDelegate<> *executeAction, size_t stackSize, ThreadCreationFlags flags) override;
};