#pragma once

#include "IClientThread.h"
#include "IRunnable.h"

using Rat::ConcurrencyModule::ThreadCreationFlags;
using Rat::ConcurrencyModule::ThreadRuntimeFlags;

class IRunnableClientThread : public IClientThread, public IRunnable {
public:
    virtual void Create(size_t stackSize, ThreadCreationFlags threadCreationFlags) = 0;
};