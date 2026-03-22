#pragma once

#include "InfiniteThread.h"
#include "RenderThreadContext.h"
#include "RenderableThreadContext.h"

class RenderThread : public InfiniteThread {
public:
    explicit RenderThread(IConcurrencyFactory* platformThreadFactory);
protected:
    void SubmitInfiniteWork() override;
};