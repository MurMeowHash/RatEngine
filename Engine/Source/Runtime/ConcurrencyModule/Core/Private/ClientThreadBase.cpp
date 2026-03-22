#include "../Public/ClientThreadBase.h"
#include "ObjectDelegate.h"
#include <cassert>
#include "CoreUtils.h"

using Rat::Core::Flags::operator&;

ClientThreadBase::ClientThreadBase(IConcurrencyFactory *concurrencyFactory)
: m_concurrencyFactory(concurrencyFactory) {
    m_workDelegate = new ObjectDelegate(this, &ClientThreadBase::SubmitWork);
}

void ClientThreadBase::Create(size_t stackSize, ThreadCreationFlags threadCreationFlags) {
    InitializeContext();
    m_threadContext.SetContextAssembled(true);
    m_platformThread = m_concurrencyFactory->CreatePlatformThread(m_workDelegate, stackSize, threadCreationFlags);
}

void ClientThreadBase::Execute() {
    assert(IsValid());
    m_platformThread->Execute();
}

uint32_t ClientThreadBase::GetThreadId() {
    if(m_platformThread == nullptr)
        return 0;

    return m_platformThread->GetThreadId();
}

bool ClientThreadBase::IsValid() {
    if(m_platformThread == nullptr)
        return false;

    return m_platformThread->IsValid();
}

ClientThreadBase::~ClientThreadBase() {
    delete m_workDelegate;
    m_threadContext.DestroyContext();
}

bool ClientThreadBase::IsRunning() {
    if(m_platformThread == nullptr)
        return false;

    return m_platformThread->IsRunning();
}

void ClientThreadBase::Terminate(bool forced) {
    assert(IsValid());
    OnRelease();
    m_platformThread->Terminate(forced);
    m_threadContext.DestroyContext();
}

void ClientThreadBase::SubmitRuntimeFlags(ThreadRuntimeFlags flags) {
    m_threadRuntimeFlags.BitwiseAdd(flags);
}

ThreadRuntimeFlags ClientThreadBase::RetrieveRuntimeFlags() {
    return m_threadRuntimeFlags.RetrieveValue();
}

void ClientThreadBase::InitializeContext() {

}

const ThreadContext &ClientThreadBase::GetThreadContext() const {
    return m_threadContext;
}