#pragma once

#include "ConcurrencyGlobals.h"
#include "IRunnableThread.h"

template<typename... Args>
class IDelegate;

using Rat::ConcurrencyModule::ThreadCreationFlags;

class IPlatformThread : public IRunnableThread {
public:
    virtual void Create(IDelegate<>* executeAction, size_t stackSize, ThreadCreationFlags flags) = 0;
};