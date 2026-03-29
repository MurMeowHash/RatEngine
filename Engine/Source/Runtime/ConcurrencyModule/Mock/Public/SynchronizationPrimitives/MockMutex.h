#pragma once

#include "SynchronizationPrimitives/IMutex.h"

class MockMutex : public IMutex {
public:
    void Create() override;
    [[nodiscard]] bool IsValid() const override;
    void LockExclusive() const override;
    void UnlockExclusive() const override;
    void LockShared() override;
    void UnlockShared() override;
    void Terminate() override;
};