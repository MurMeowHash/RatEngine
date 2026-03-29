#pragma once

#include "ConcurrencyGlobals.h"
#include "IRunnable.h"
#include "IThread.h"

template<typename... Args>
class IDelegate;

using Rat::ConcurrencyModule::ThreadCreationFlags;

class IPlatformThread : public IThread, public IRunnable {
public:
    virtual void Create(IDelegate<>* executeAction, size_t stackSize, ThreadCreationFlags flags) = 0;
};