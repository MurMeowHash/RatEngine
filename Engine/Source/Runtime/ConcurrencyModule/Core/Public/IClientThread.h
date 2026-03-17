#pragma once

#include <cstddef>
#include "ConcurrencyGlobals.h"
#include "IThread.h"

using Rat::ConcurrencyModule::ThreadCreationFlags;
using Rat::ConcurrencyModule::ThreadRuntimeFlags;

class IClientThread : public IThread {
public:
    virtual void Create(size_t stackSize, ThreadCreationFlags threadCreationFlags) = 0;
    virtual void SubmitRuntimeFlags(ThreadRuntimeFlags flags) = 0;
};