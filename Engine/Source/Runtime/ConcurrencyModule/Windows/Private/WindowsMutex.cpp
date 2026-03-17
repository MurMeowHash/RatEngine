#include "WindowsMutex.h"
#include <cassert>

void WindowsMutex::Create(bool initiallyLocked) {
    m_mutexHandle = CreateMutexA(nullptr, initiallyLocked, nullptr);
}

void WindowsMutex::Lock() {
    assert(IsValid());
    WaitForSingleObject(m_mutexHandle, INFINITE);
}

void WindowsMutex::Unlock() {
    assert(IsValid());
    ReleaseMutex(m_mutexHandle);
}

bool WindowsMutex::IsValid() {
    return m_mutexHandle != nullptr;
}

void WindowsMutex::Terminate() {
    Unlock();
    CloseHandle(m_mutexHandle);
    m_mutexHandle = nullptr;
}
