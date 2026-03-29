#pragma once

#include "IMutex.h"

class ExclusiveThreadGuard {
public:
    explicit ExclusiveThreadGuard(IMutex* mutex) {
        m_mutex = mutex;
        m_mutex->LockExclusive();
    }

    ~ExclusiveThreadGuard() {
        m_mutex->UnlockExclusive();
    }

private:
    IMutex* m_mutex;
};