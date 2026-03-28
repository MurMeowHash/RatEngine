#include "WindowsMutex.h"
#include <cassert>

void WindowsMutex::Create(bool initiallyLocked) {
    m_mutexHandle = CreateMutexA(nullptr, initiallyLocked, nullptr);
}

void WindowsMutex::Lock() const {
    assert(IsValid());
    WaitForSingleObject(m_mutexHandle, INFINITE);
}

void WindowsMutex::Unlock() const {
    assert(IsValid());
    ReleaseMutex(m_mutexHandle);
}

bool WindowsMutex::IsValid() const {
    return m_mutexHandle != nullptr;
}

void WindowsMutex::Terminate() {
    Unlock();
    CloseHandle(m_mutexHandle);
    m_mutexHandle = nullptr;
}
