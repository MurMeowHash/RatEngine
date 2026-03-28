#pragma once

#include "IMutex.h"
#include <windows.h>

class WindowsMutex : public IMutex {
public:
    void Create(bool initiallyLocked) override;
    void Lock() const override;
    void Unlock() const override;
    [[nodiscard]] bool IsValid() const override;
    void Terminate() override;

private:
    HANDLE m_mutexHandle = nullptr;
};