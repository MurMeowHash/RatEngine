#pragma once

#include "IClientThread.h"

class IClientThreadWrapper : public IClientThread {
public:
    virtual void Initialize() = 0;
    virtual void Initialize(uint32_t existingThreadId) = 0;
};