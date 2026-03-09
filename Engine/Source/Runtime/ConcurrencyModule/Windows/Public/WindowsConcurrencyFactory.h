#pragma once

#include "IConcurrencyFactory.h"

class WindowsConcurrencyFactory : public IConcurrencyFactory {
public:
    IPlatformThread* CreatePlatformThread(IDelegate<> *executeAction, size_t stackSize, ThreadCreationFlags flags) override;
};