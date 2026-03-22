#include "InfiniteThread.h"

InfiniteThread::InfiniteThread(IConcurrencyFactory *concurrencyFactory)
: ClientThreadBase(concurrencyFactory) { }

void InfiniteThread::InitializeContext() {
    ClientThreadBase::InitializeContext();
    m_threadContext.AddContextUnit(new InfiniteThreadContext);
}

void InfiniteThread::SubmitWork() {
    while(!Rat::Core::Flags::IsFlagSet(RetrieveRuntimeFlags(), ThreadRuntimeFlags::StopRequested)) {
        SubmitInfiniteWork();
    }
}
