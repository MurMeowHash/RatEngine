#pragma once

#include "PlatformInteractors/IPlatformInteractor.h"

class MockPlatformInteractor : public IPlatformInteractor {
public:
    void RequestQuit(bool forcedQuit) override {}
    uint32_t GetRunningThreadId() override { return 0; }
};