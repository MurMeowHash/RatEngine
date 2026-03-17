#pragma once

#include <cstdint>

class IThread {
public:
    virtual void Execute() = 0;
    [[nodiscard]] virtual uint32_t GetThreadId() = 0;
    [[nodiscard]] virtual bool IsValid() = 0;
    [[nodiscard]] virtual bool IsRunning() = 0;
    virtual void Terminate(bool forced) = 0;
    virtual ~IThread() = default;
};