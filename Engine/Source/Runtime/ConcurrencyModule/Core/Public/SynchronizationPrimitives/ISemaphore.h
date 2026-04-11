#pragma once

#include <cstdint>

class ISemaphore {
public:
    virtual void Create(int32_t initialUsages, int32_t maxUsages) = 0;
    virtual void Acquire() = 0;
    virtual void Release() = 0;
    virtual void Terminate() = 0;
    [[nodiscard]] virtual bool IsValid() const = 0;
    virtual ~ISemaphore() = default;
};