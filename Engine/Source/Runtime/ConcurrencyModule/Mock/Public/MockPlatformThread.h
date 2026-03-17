#pragma once

#include "IPlatformThread.h"

class MockPlatformThread : public IPlatformThread {
public:
    void Create(IDelegate<>* executeAction, size_t stackSize, ThreadCreationFlags flags) override;
    void Execute() override;
    uint32_t GetThreadId() override;
    bool IsValid() override;
    bool IsRunning() override;
    void Terminate(bool forced) override;
};