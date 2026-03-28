#pragma once

#include "IPlatformThread.h"
#include <windows.h>

class WindowsPlatformThread : public IPlatformThread {
public:
    void Execute() override;

public:
    uint32_t GetThreadId() override;
    bool IsValid() override;
    bool IsRunning() override;

    void Terminate(bool forced) override;

public:
    void Create(IDelegate<>* executeAction, size_t stackSize, ThreadCreationFlags flags) override;

private:
    DWORD m_threadId = 0;
    HANDLE m_threadHandle = nullptr;
    bool m_isScheduled = false;
    static DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter);

    void ReleaseThread();
};