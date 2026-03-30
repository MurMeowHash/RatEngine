#include "InfiniteThread.h"
#include "InfiniteThreadContext.h"

InfiniteThread::InfiniteThread(IConcurrencyFactory *concurrencyFactory, ThreadStorage* threadStorage, IPlatformInteractor* platformInteractor)
: ClientThreadBase(concurrencyFactory, threadStorage, platformInteractor) { }

void InfiniteThread::InitializeContext() {
    ClientThreadBase::InitializeContext();
    uint64_t authorityFrameIndex = 0;
    if (m_authorityThread != nullptr) {
        InfiniteThreadContext* authorityInfiniteThreadContext;
        if (m_authorityThread->GetThreadContext()->TryRetrieveContextUnit(authorityInfiniteThreadContext))
            authorityFrameIndex = authorityInfiniteThreadContext->m_threadFrameIndex.RetrieveValue();

    }
    m_threadContext->AddContextUnit(new InfiniteThreadContext(authorityFrameIndex));
}

void InfiniteThread::SubmitWork() {
    OnBeforeWork();
    while(!Rat::Core::Flags::IsFlagSet(RetrieveRuntimeFlags(), ThreadRuntimeFlags::StopRequested)) {
        SubmitInfiniteWork();
    }

    OnAfterWork();
}
