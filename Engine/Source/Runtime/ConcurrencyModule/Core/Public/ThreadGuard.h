#pragma once

#include "IMutex.h"

class ThreadGuard {
public:
    explicit ThreadGuard(IMutex* mutex) {
        m_mutex = mutex;
        m_mutex->Lock();
    }

    ~ThreadGuard() {
        m_mutex->Unlock();
    }

private:
    IMutex* m_mutex;
};