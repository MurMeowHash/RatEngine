#pragma once

#include "InfiniteThread.h"
#include "RenderThreadContext.h"

class RenderThread : public InfiniteThread {
public:
    explicit RenderThread(IConcurrencyFactory* platformThreadFactory);
protected:
    void SubmitInfiniteWork() override;
};