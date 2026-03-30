#include "WorldThreadWrapper.h"
#include "PlatformInteractors/IPlatformInteractor.h"
#include "ThreadContext.h"
#include "InfiniteThreadContext.h"
#include "ProjectSettings/ProjectSettings.h"
#include "ThreadStorage.h"
#include "CommandProducerThreadContext.h"
#include "RenderThreadGlobals.h"
#include "LinearAllocator.h"
#include "SynchronizationPrimitives/Fence.h"
#include "IConcurrencyFactory.h"

WorldThreadWrapper::WorldThreadWrapper(IPlatformInteractor *platformInteractor, ProjectSettings* projectSettings,
    ThreadStorage* threadStorage, IConcurrencyFactory* concurrencyFactory)
: m_platformInteractor(platformInteractor), m_projectSettings(projectSettings), m_threadStorage(threadStorage),
m_concurrencyFactory(concurrencyFactory) { }

void WorldThreadWrapper::Initialize() {
    Initialize(m_platformInteractor->GetRunningThreadId());
}

void WorldThreadWrapper::Initialize(uint32_t existingThreadId) {
    m_threadStorage->Store(this);
    m_threadId = existingThreadId;
    InitializeContext();
    m_threadContext->SetContextAssembled(true);
    m_isRunning = true;
    m_commandBufferAllocator = new LinearAllocator(m_projectSettings->GetMemoryAllocationSettings().m_commandBufferChunkSize);
    Fence fence(m_concurrencyFactory);
}

void WorldThreadWrapper::SubmitRuntimeFlags(ThreadRuntimeFlags flags) {
    if (Rat::Core::Flags::IsFlagSet(flags, ThreadRuntimeFlags::StopRequested))
        m_isRunning = false;
}

ThreadContext* WorldThreadWrapper::GetThreadContext() const {
    return m_threadContext;
}

uint32_t WorldThreadWrapper::GetThreadAuthority() {
    return GetThreadId();
}

bool WorldThreadWrapper::HasThreadAuthority() {
    return m_platformInteractor->GetRunningThreadId() == GetThreadAuthority();
}

uint32_t WorldThreadWrapper::GetThreadId() {
    return m_threadId;
}

bool WorldThreadWrapper::IsValid() {
    return m_threadId != 0;
}

bool WorldThreadWrapper::IsRunning() {
    return m_isRunning;
}

void WorldThreadWrapper::Terminate([[maybe_unused]] bool forced) {
    m_threadContext->DestroyContext();
    delete m_threadContext;
    m_commandBufferAllocator->FreeMemory();
    delete m_commandBufferAllocator;
    m_threadStorage->DeleteFromStorage(this);
    m_isRunning = false;
}

void WorldThreadWrapper::InitializeContext() {
    m_threadContext = new ThreadContext();

    m_threadContext->AddContextUnit(new InfiniteThreadContext(0));
    m_threadContext->AddContextUnit(new CommandProducerThreadContext<RenderCommand>(m_commandBufferAllocator));
}