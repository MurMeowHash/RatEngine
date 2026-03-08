#include "../Public/WindowsPlatformThread.h"
#include <winbase.h>
#include <winnt.h>
#include "CoreUtils.h"
#include "IDelegate.h"
#include <cassert>

void WindowsPlatformThread::Create(IDelegate<>* executeAction, size_t stackSize, ThreadCreationFlags flags) {
    DWORD windowsThreadFlags = 0;
    if(Rat::Core::Flags::IsFlagSet(flags, ThreadCreationFlags::Deferred))
        windowsThreadFlags |= CREATE_SUSPENDED;
    m_threadHandle = CreateThread(nullptr, stackSize, ThreadProc,
                                  (LPDWORD)executeAction, windowsThreadFlags, &m_threadId);

    m_isScheduled = (windowsThreadFlags & CREATE_SUSPENDED) == 0 && IsValid();
}

void WindowsPlatformThread::Execute() {
    assert(IsValid());

    if(m_isScheduled)
        return;

    ResumeThread(m_threadHandle);
}

uint32_t WindowsPlatformThread::GetThreadId() {
    return m_threadId;
}

DWORD WINAPI WindowsPlatformThread::ThreadProc(LPVOID lpParameter) {
    IDelegate<>* callableAction = static_cast<IDelegate<>*>(lpParameter);
    callableAction->Invoke();
    return 0;
}

bool WindowsPlatformThread::IsValid() {
    return m_threadHandle != nullptr;
}

bool WindowsPlatformThread::IsRunning() {
    if(m_threadHandle == nullptr)
        return false;

    DWORD exitCode;
    GetExitCodeThread(m_threadHandle, &exitCode);
    return exitCode == STILL_ACTIVE;
}

void WindowsPlatformThread::Terminate(bool forced) {
    assert(IsValid());

    if(!IsRunning()) {
        ReleaseThread();
        return;
    }

    if(!forced)
        WaitForSingleObject(m_threadHandle, INFINITE);

    ReleaseThread();
}

void WindowsPlatformThread::ReleaseThread() {
    CloseHandle(m_threadHandle);
    m_threadId = 0;
    m_threadHandle = nullptr;
}

void WindowsPlatformThread::SetSynchronizedValue64(uint64_t *destination, uint64_t value) {
    InterlockedExchange(destination, value);
}

uint64_t WindowsPlatformThread::GetSynchronizedValue64(uint64_t *targetMem) {
    return InterlockedCompareExchange(targetMem, 0, 0);
}

void WindowsPlatformThread::SetSynchronizedBitwiseOrValue64(uint64_t *destination, uint64_t bitwiseOperand) {
    InterlockedOr(destination, bitwiseOperand);
}