#pragma once

#include "IMutex.h"
#include <windows.h>

class WindowsMutex : public IMutex {
public:
    void Create(bool initiallyLocked) override;
    void Lock() override;
    void Unlock() override;
    bool IsValid() override;
    void Terminate() override;

private:
    HANDLE m_mutexHandle;
};