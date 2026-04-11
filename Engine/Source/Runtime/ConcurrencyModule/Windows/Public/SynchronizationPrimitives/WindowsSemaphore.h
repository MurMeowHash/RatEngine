#pragma once

#include "SynchronizationPrimitives/ISemaphore.h"
#include <windows.h>

class WindowsSemaphore : public ISemaphore {
public:
    void Create(int32_t initialUsages, int32_t maxUsages) override;
    void Acquire() override;
    void Release() override;
    void Terminate() override;
    [[nodiscard]] bool IsValid() const override;
private:
    HANDLE m_semaphore = nullptr;
};