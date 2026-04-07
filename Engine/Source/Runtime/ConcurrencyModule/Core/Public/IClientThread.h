#pragma once

#include "ConcurrencyGlobals.h"
#include "ThreadContext.h"
#include "IThread.h"

using Rat::ConcurrencyModule::ThreadRuntimeFlags;

class IClientThread : public IThread {
public:
    virtual void SubmitRuntimeFlags(ThreadRuntimeFlags flags) = 0;
    [[nodiscard]] virtual ThreadContext* GetThreadContext() const = 0;
};