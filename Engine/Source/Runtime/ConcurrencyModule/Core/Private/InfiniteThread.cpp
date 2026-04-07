#include "InfiniteThread.h"
#include "InfiniteThreadContext.h"

InfiniteThread::InfiniteThread(IConcurrencyFactory *concurrencyFactory, ThreadStorage* threadStorage)
: ClientThreadBase(concurrencyFactory, threadStorage) { }

void InfiniteThread::InitializeContext() {
    ClientThreadBase::InitializeContext();
    m_threadContext->AddContextUnit(new InfiniteThreadContext());
}

void InfiniteThread::SubmitThreadWork() {
    while(!Rat::Core::Flags::IsFlagSet(RetrieveRuntimeFlags(), ThreadRuntimeFlags::StopRequested)) {
        SubmitInfiniteWork();
    }
}
