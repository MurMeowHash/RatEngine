#pragma once

#include "ClientThreadBase.h"
#include "InfiniteThreadContext.h"

class InfiniteThread : public ClientThreadBase {
public:
    InfiniteThread(IConcurrencyFactory* concurrencyFactory, ThreadStorage* threadStorage);
protected:
    void InitializeContext() override;
    void SubmitWork() override;

    virtual void SubmitInfiniteWork() = 0;
    virtual void OnBeforeWork() {}
    virtual void OnAfterWork() {}
};