#pragma once

#include "ClientThreadBase.h"

class InfiniteThread : public ClientThreadBase {
public:
    InfiniteThread(IConcurrencyFactory* concurrencyFactory, ThreadStorage* threadStorage, EngineCoreEventBus* engineCoreEventBus);
protected:
    void InitializeContext() override;
    void SubmitThreadWork() override;

    virtual void SubmitInfiniteWork() = 0;
};