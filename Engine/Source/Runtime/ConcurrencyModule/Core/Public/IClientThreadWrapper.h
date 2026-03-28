#pragma once

#include "ThreadContext.h"
#include "IThread.h"

class IClientThreadWrapper : public IThread {
public:
    virtual void Initialize() = 0;
    virtual void Initialize(uint32_t existingThreadId) = 0;
    virtual void Dispose() = 0;
    [[nodiscard]] virtual ThreadContext* GetThreadContext() const = 0;
};