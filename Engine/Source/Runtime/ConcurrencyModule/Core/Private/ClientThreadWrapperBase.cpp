#include "../Public/ClientThreadWrapperBase.h"
#include "PlatformInteractors/IPlatformInteractor.h"
#include "ThreadContext.h"
#include "ThreadStorage.h"
#include "SynchronizationPrimitives/Fence.h"
#include "IConcurrencyFactory.h"
#include "ThreadProcessor.h"
#include "DiContainer.h"
#include "EngineCoreEventBus.h"
#include "ObjectDelegate.h"

ClientThreadWrapperBase::ClientThreadWrapperBase(IPlatformInteractor *platformInteractor, ThreadStorage* threadStorage,
    IConcurrencyFactory* concurrencyFactory, EngineCoreEventBus* engineCoreEventBus)
: m_engineCoreEventBus(engineCoreEventBus), m_platformInteractor(platformInteractor), m_threadStorage(threadStorage), m_concurrencyFactory(concurrencyFactory) {
    m_invokeMemoryBarrierCallback = new ObjectDelegate<ClientThreadWrapperBase, IClientThread*>(this, &ClientThreadWrapperBase::InvokeMemoryBarrier);
}

ClientThreadWrapperBase::~ClientThreadWrapperBase() {
    delete m_invokeMemoryBarrierCallback;
}

void ClientThreadWrapperBase::Initialize() {
    Initialize(m_platformInteractor->GetRunningThreadId());
}

void ClientThreadWrapperBase::Initialize(uint32_t existingThreadId) {
    m_threadId = existingThreadId;

    InitializeContext();
    m_threadContext->SetContextAssembled(true);
    m_isRunning = true;
    Fence fence(m_concurrencyFactory);
    m_threadStorage->Store(this);

    OnThreadBegin();
}

void ClientThreadWrapperBase::InitializeContext() {
    m_threadContext = new ThreadContext();
}

void ClientThreadWrapperBase::OnThreadBegin() {
    InvokeMemoryBarrier(nullptr);
    m_threadStorage->m_onThreadAdded->Subscribe(m_invokeMemoryBarrierCallback);
    m_threadProcessor = new ThreadProcessor(GetThreadId());
}

void ClientThreadWrapperBase::OnThreadEnd() {
    m_threadStorage->m_onThreadAdded->UnSubscribe(m_invokeMemoryBarrierCallback);

    m_threadProcessor->TerminateProcessor();
    delete m_threadProcessor;
}

void ClientThreadWrapperBase::SubmitRuntimeFlags(ThreadRuntimeFlags flags) {
    if (Rat::Core::Flags::IsFlagSet(flags, ThreadRuntimeFlags::StopRequested)) {
        OnThreadEnd();
        m_isRunning = false;
    }
}

ThreadContext* ClientThreadWrapperBase::GetThreadContext() const {
    return m_threadContext;
}

uint32_t ClientThreadWrapperBase::GetThreadId() {
    return m_threadId;
}

bool ClientThreadWrapperBase::IsValid() {
    return m_threadId != 0;
}

bool ClientThreadWrapperBase::IsRunning() {
    return m_isRunning;
}

void ClientThreadWrapperBase::Terminate([[maybe_unused]] bool forced) {
    m_threadContext->DestroyContext();
    delete m_threadContext;
    m_threadStorage->DeleteFromStorage(this);
    m_isRunning = false;
}

void ClientThreadWrapperBase::InvokeMemoryBarrier([[maybe_unused]] IClientThread *clientThread) {
    Fence fence(m_concurrencyFactory);
}