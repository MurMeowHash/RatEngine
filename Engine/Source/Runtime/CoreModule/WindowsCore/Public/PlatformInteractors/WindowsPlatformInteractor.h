#pragma once

#include "PlatformInteractors/IPlatformInteractor.h"

class WindowsPlatformInteractor : public IPlatformInteractor {
public:
    explicit WindowsPlatformInteractor();
    void RequestQuit(bool forcedQuit) override;
    uint32_t GetRunningThreadId() override;
    [[nodiscard]] PlatformRuntimeData GetPlatformRuntimeData() override;

private:
    PlatformRuntimeData m_platformRuntimeData;

    void CreatePlatformRuntimeData();
};