#pragma once

#include <cstdint>
#include "ThreadContext.h"

class IThreadWrapper {
public:
    virtual void Initialize() = 0;
    virtual void Dispose() = 0;
    virtual uint32_t GetThreadId() = 0;
    [[nodiscard]] virtual ThreadContext* GetThreadContext() const = 0;
    virtual ~IThreadWrapper() = default;
};