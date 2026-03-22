#pragma once

#include "ClientThreadBase.h"
#include "InfiniteThreadContext.h"

class InfiniteThread : public ClientThreadBase {
public:
    explicit InfiniteThread(IConcurrencyFactory* concurrencyFactory);
protected:
    void InitializeContext() override;
    void SubmitWork() override;

    virtual void SubmitInfiniteWork() = 0;
};