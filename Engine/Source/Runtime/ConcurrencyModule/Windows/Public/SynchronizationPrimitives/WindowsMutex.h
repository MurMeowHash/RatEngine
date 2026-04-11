#pragma once

#include "SynchronizationPrimitives/IMutex.h"
#include <windows.h>

class WindowsMutex : public IMutex {
public:
    void Create() override;
    [[nodiscard]] bool IsValid() const override;
    void LockExclusive() const override;
    void UnlockExclusive() const override;
    void LockShared() override;
    void UnlockShared() override;
    void Terminate() override;
private:
    PSRWLOCK m_lock = nullptr;
};