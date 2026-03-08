#pragma once

#include <cstddef>
#include "ConcurrencyGlobals.h"
#include "IThread.h"

template<typename... Args>
class IDelegate;

using Rat::ConcurrencyModule::ThreadCreationFlags;

class IPlatformThread : public IThread {
public:
    virtual void Create(IDelegate<>* executeAction, size_t stackSize, ThreadCreationFlags flags) = 0;
    virtual void SetSynchronizedValue64(uint64_t* destination, uint64_t value) = 0;
    [[nodiscard]] virtual uint64_t GetSynchronizedValue64(uint64_t* targetMem) = 0;
    virtual void SetSynchronizedBitwiseOrValue64(uint64_t *destination, uint64_t bitwiseOperand) = 0;
};