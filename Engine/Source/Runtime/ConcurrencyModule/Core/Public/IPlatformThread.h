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
};