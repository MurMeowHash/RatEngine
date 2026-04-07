#include "../Public/WindowsPlatformThread.h"
#include "CoreUtils.h"
#include "IDelegate.h"
#include <cassert>
#include "SynchronizationPrimitives/WindowsFence.h"

void WindowsPlatformThread::Create(IDelegate<>* executeAction, size_t stackSize, ThreadCreationFlags flags) {
    DWORD windowsThreadFlags = 0;
    if(Rat::Core::Flags::IsFlagSet(flags, ThreadCreationFlags::Deferred))
        windowsThreadFlags |= CREATE_SUSPENDED;
    m_threadHandle = CreateThread(nullptr, stackSize, ThreadProc,
                                  (LPDWORD)executeAction, windowsThreadFlags, &m_threadId);

    m_isScheduled = (windowsThreadFlags & CREATE_SUSPENDED) == 0 && IsValid();
    WindowsFence(true);
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

    if (forced)
        TerminateThread(m_threadHandle, 0); // TODO: potential memory leak from thread owned resources
    else
        WaitForSingleObject(m_threadHandle, INFINITE);

    ReleaseThread();
}

void WindowsPlatformThread::ReleaseThread() {
    CloseHandle(m_threadHandle);
    m_threadId = 0;
    m_threadHandle = nullptr;
}