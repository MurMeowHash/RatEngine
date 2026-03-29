#pragma once

#include "IMutex.h"

class SharedThreadGuard {
public:
    explicit SharedThreadGuard(IMutex* mutex) {
        m_mutex = mutex;
        m_mutex->LockShared();
    }

    ~SharedThreadGuard() {
        m_mutex->UnlockShared();
    }

private:
    IMutex* m_mutex;
};