#include "InfiniteThread.h"

InfiniteThread::InfiniteThread(IConcurrencyFactory *concurrencyFactory)
: ClientThreadBase(concurrencyFactory) { }

void InfiniteThread::InitializeContext() {
    ClientThreadBase::InitializeContext();
    InfiniteThreadContext* infiniteThreadContext = new InfiniteThreadContext;
    m_cachedInfiniteThreadContext.StoreValue(infiniteThreadContext);
    m_threadContext.AddContextUnit(infiniteThreadContext);
}

void InfiniteThread::Terminate(bool forced) {
    ClientThreadBase::Terminate(forced);
    delete m_cachedInfiniteThreadContext.RetrieveValue();
}

void InfiniteThread::SubmitWork() {
    while(!Rat::Core::Flags::IsFlagSet(RetrieveRuntimeFlags(), ThreadRuntimeFlags::StopRequested)) {
        SubmitInfiniteWork();
    }
}
