#include "../Public/ClientThreadBase.h"
#include "ObjectDelegate.h"
#include <cassert>
#include "CoreUtils.h"
#include "SynchronizationPrimitives/Fence.h"
#include "EngineCoreEventBus.h"

using Rat::Core::Flags::operator&;

ClientThreadBase::ClientThreadBase(IConcurrencyFactory *concurrencyFactory, ThreadStorage* threadStorage, EngineCoreEventBus* engineCoreEventBus)
: m_concurrencyFactory(concurrencyFactory), m_threadStorage(threadStorage), m_engineCoreEventBus(engineCoreEventBus) {
    m_workDelegate = new ObjectDelegate(this, &ClientThreadBase::SubmitWork);
    m_invokeMemoryBarrierCallback = new ObjectDelegate<ClientThreadBase, IClientThread*>(this, &ClientThreadBase::InvokeMemoryBarrier);
}

void ClientThreadBase::Create(size_t stackSize, ThreadCreationFlags threadCreationFlags) {
    InitializeContext();
    m_threadContext->SetContextAssembled(true);
    m_platformThread = m_concurrencyFactory->CreatePlatformThread(m_workDelegate, stackSize, threadCreationFlags);
    m_threadStorage->Store(this);
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
    delete m_invokeMemoryBarrierCallback;
}

bool ClientThreadBase::IsRunning() {
    if(m_platformThread == nullptr)
        return false;

    return m_platformThread->IsRunning();
}

void ClientThreadBase::Terminate(bool forced) {
    assert(IsValid());
    m_platformThread->Terminate(forced);
    m_threadContext->DestroyContext();
    m_threadStorage->DeleteFromStorage(this);

    delete m_platformThread;
    delete m_threadContext;
}

void ClientThreadBase::SubmitRuntimeFlags(ThreadRuntimeFlags flags) {
    m_threadRuntimeFlags.BitwiseAdd(flags);
}

ThreadRuntimeFlags ClientThreadBase::RetrieveRuntimeFlags() {
    return m_threadRuntimeFlags.RetrieveValue();
}

void ClientThreadBase::InitializeContext() {
    m_threadContext = new ThreadContext();
}

void ClientThreadBase::OnThreadBegin() {
    InvokeMemoryBarrier(nullptr);
    m_threadStorage->m_onThreadAdded->Subscribe(m_invokeMemoryBarrierCallback);
    m_threadProcessor = new ThreadProcessor(GetThreadId());
}

void ClientThreadBase::OnThreadEnd() {
    m_threadStorage->m_onThreadAdded->UnSubscribe(m_invokeMemoryBarrierCallback);
    m_threadProcessor->TerminateProcessor();
    delete m_threadProcessor;
}

void ClientThreadBase::SubmitWork() {
    OnThreadBegin();
    SubmitThreadWork();
    OnThreadEnd();
}

void ClientThreadBase::InvokeMemoryBarrier([[maybe_unused]] IClientThread *clientThread) {
    Fence fence(m_concurrencyFactory);
}

ThreadContext* ClientThreadBase::GetThreadContext() const {
    return m_threadContext;
}
