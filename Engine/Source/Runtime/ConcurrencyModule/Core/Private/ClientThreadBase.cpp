#include "../Public/ClientThreadBase.h"
#include "ObjectDelegate.h"
#include <cassert>
#include "CoreUtils.h"

using Rat::Core::Flags::operator&;

ClientThreadBase::ClientThreadBase(IPlatformThreadFactory *platformThreadFactory)
: m_platformThreadFactory(platformThreadFactory) {
    m_workDelegate = new ObjectDelegate(this, &ClientThreadBase::SubmitWork);
}

void ClientThreadBase::Create(size_t stackSize, ThreadCreationFlags threadCreationFlags) {
    m_platformThread = m_platformThreadFactory->CreatePlatformThread(m_workDelegate, stackSize, threadCreationFlags);
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
}

void ClientThreadBase::SubmitRuntimeFlags(ThreadRuntimeFlags flags) {
    uint64_t* convertedRuntimeFlagsMem = reinterpret_cast<uint64_t*>(&m_threadRuntimeFlags);
    m_platformThread->SetSynchronizedBitwiseOrValue64(convertedRuntimeFlagsMem, static_cast<uint64_t>(flags));
}

ThreadRuntimeFlags ClientThreadBase::RetrieveRuntimeFlags() {
    uint64_t* convertedRuntimeFlagsMem = reinterpret_cast<uint64_t*>(&m_threadRuntimeFlags);
    return static_cast<ThreadRuntimeFlags>(m_platformThread->GetSynchronizedValue64(convertedRuntimeFlagsMem));
}
