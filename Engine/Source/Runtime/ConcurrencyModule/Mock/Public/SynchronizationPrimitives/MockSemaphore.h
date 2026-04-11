#pragma once

#include "SynchronizationPrimitives/ISemaphore.h"

class MockSemaphore : public ISemaphore {
public:
    void Create(int32_t initialUsages, int32_t maxUsages) override;
    void Acquire() override;
    void Release() override;
    void Terminate() override;
    [[nodiscard]] bool IsValid() const override;
};