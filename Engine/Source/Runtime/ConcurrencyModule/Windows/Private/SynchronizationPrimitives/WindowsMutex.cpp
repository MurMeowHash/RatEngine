#include "../../Public/SynchronizationPrimitives/WindowsMutex.h"
#include <cassert>

void WindowsMutex::Create() {
    m_lock = new SRWLOCK();
    InitializeSRWLock(m_lock);
}

bool WindowsMutex::IsValid() const {
    return m_lock != nullptr;
}

void WindowsMutex::LockExclusive() const {
    assert(IsValid());
    AcquireSRWLockExclusive(m_lock);
}

void WindowsMutex::UnlockExclusive() const {
    assert(IsValid());
    ReleaseSRWLockExclusive(m_lock);
}

void WindowsMutex::LockShared() {
    assert(IsValid());
    AcquireSRWLockShared(m_lock);
}

void WindowsMutex::UnlockShared() {
    assert(IsValid());
    ReleaseSRWLockShared(m_lock);
}

void WindowsMutex::Terminate() {
    delete m_lock;
    m_lock = nullptr;
}
