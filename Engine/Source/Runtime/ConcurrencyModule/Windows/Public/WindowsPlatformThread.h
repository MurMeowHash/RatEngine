#pragma once

#include "IPlatformThread.h"
#include <processthreadsapi.h>

class WindowsPlatformThread : public IPlatformThread {
public:
    void Execute() override;

    uint32_t GetThreadId() override;
    bool IsValid() override;
    bool IsRunning() override;

    void Terminate(bool forced) override;

public:
    void Create(IDelegate<>* executeAction, size_t stackSize, ThreadCreationFlags flags) override;
    void SetSynchronizedValue64(uint64_t *destination, uint64_t value) override;
    uint64_t GetSynchronizedValue64(uint64_t *targetMem) override;
    void SetSynchronizedBitwiseOrValue64(uint64_t *destination, uint64_t bitwiseOperand) override;

private:
    DWORD m_threadId = 0;
    HANDLE m_threadHandle = nullptr;
    bool m_isScheduled = false;
    static DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter);

    void ReleaseThread();
};