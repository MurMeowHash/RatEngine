#pragma once

#include "ClientThreadBase.h"
#include "SynchronizationCommon.h"
#include "InfiniteThreadContext.h"

class InfiniteThread : public ClientThreadBase {
public:
    explicit InfiniteThread(IConcurrencyFactory* concurrencyFactory);
    void Terminate(bool forced) override;
protected:
    void InitializeContext() override;
    void SubmitWork() override;

    virtual void SubmitInfiniteWork() = 0;

private:
    AtomicSynchronizer<InfiniteThreadContext*> m_cachedInfiniteThreadContext = AtomicSynchronizer<InfiniteThreadContext*>(nullptr);
};