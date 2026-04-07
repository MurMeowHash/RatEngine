#include "WorldThreadWrapper.h"
#include "PlatformInteractors/IPlatformInteractor.h"
#include "ThreadContext.h"
#include "InfiniteThreadContext.h"
#include "ProjectSettings/ProjectSettings.h"
#include "ThreadStorage.h"
#include "CommandProducerThreadContext.h"
#include "LinearAllocator.h"
#include "SynchronizationPrimitives/Fence.h"
#include "IConcurrencyFactory.h"
#include "RenderCommand.h"
#include "ThreadProcessor.h"
#include "FrameCommandSubmitSystem.h"
#include "DiContainer.h"
#include "FrameLagContext.h"
#include "RenderThread.h"
#include "FrameLagConstraintSystem.h"
#include "FrameIncrementSystem.h"
#include "ObjectDelegate.h"

WorldThreadWrapper::WorldThreadWrapper(IPlatformInteractor *platformInteractor, ProjectSettings* projectSettings,
    ThreadStorage* threadStorage, IConcurrencyFactory* concurrencyFactory, DiContainer* diContainer)
: m_platformInteractor(platformInteractor), m_projectSettings(projectSettings), m_threadStorage(threadStorage),
m_concurrencyFactory(concurrencyFactory), m_diContainer(diContainer) {
    m_invokeMemoryBarrierCallback = new ObjectDelegate<WorldThreadWrapper, IClientThread*>(this, &WorldThreadWrapper::InvokeMemoryBarrier);
}

WorldThreadWrapper::~WorldThreadWrapper() {
    delete m_invokeMemoryBarrierCallback;
}

void WorldThreadWrapper::Initialize() {
    Initialize(m_platformInteractor->GetRunningThreadId());
}

void WorldThreadWrapper::Initialize(uint32_t existingThreadId) {
    m_threadId = existingThreadId;
    m_commandBufferAllocator = new LinearAllocator(m_projectSettings->GetMemoryAllocationSettings().m_commandBufferChunkSize);

    InitializeContext();
    m_threadContext->SetContextAssembled(true);
    m_isRunning = true;
    Fence fence(m_concurrencyFactory);
    m_threadStorage->Store(this);

    InitializeProcessor();

    m_threadStorage->m_onThreadAdded->Subscribe(m_invokeMemoryBarrierCallback);
}

void WorldThreadWrapper::SubmitRuntimeFlags(ThreadRuntimeFlags flags) {
    if (Rat::Core::Flags::IsFlagSet(flags, ThreadRuntimeFlags::StopRequested))
        m_isRunning = false;
}

ThreadContext* WorldThreadWrapper::GetThreadContext() const {
    return m_threadContext;
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
    m_threadStorage->m_onThreadAdded->UnSubscribe(m_invokeMemoryBarrierCallback);

    m_threadProcessor->TerminateProcessor();
    delete m_threadProcessor;
    m_threadContext->DestroyContext();
    delete m_threadContext;
    m_commandBufferAllocator->FreeMemory();
    delete m_commandBufferAllocator;
    m_threadStorage->DeleteFromStorage(this);
    m_isRunning = false;
}

void WorldThreadWrapper::InitializeContext() {
    m_threadContext = new ThreadContext();

    m_threadContext->AddContextUnit(new InfiniteThreadContext());
    CommandProducerThreadContext<RenderCommand>* commandProducerContext =
        m_diContainer->Instantiate<CommandProducerThreadContext<RenderCommand>>().WithArguments<ThreadSearchService>();
    commandProducerContext->Initialize(m_commandBufferAllocator);
    m_threadContext->AddContextUnit(commandProducerContext);
    FrameLagContext<RenderThread>* frameLagContext = m_diContainer->Instantiate<FrameLagContext<RenderThread>>().WithArguments<IConcurrencyFactory>();
    int32_t maxFrameLag = m_projectSettings->GetRenderingSettings().m_maxFrameLag;
    frameLagContext->Initialize(maxFrameLag, maxFrameLag);
    m_threadContext->AddContextUnit(frameLagContext);
}

void WorldThreadWrapper::InitializeProcessor() {
    m_threadProcessor = new ThreadProcessor(GetThreadId());
    m_threadProcessor->AddSystem<FrameCommandSubmitSystem<RenderCommand>>(m_diContainer->Resolve<EngineCoreEventBus>(),
        m_diContainer->Resolve<ThreadSearchService>(), m_diContainer->Resolve<CommandThreadStorage>());

    m_threadProcessor->AddSystem<FrameLagConstraintSystem<WorldThreadWrapper, RenderThread>>(m_diContainer->Resolve<ThreadSearchService>(),
        m_diContainer->Resolve<EngineCoreEventBus>());

    m_threadProcessor->AddSystem<FrameIncrementSystem>(m_diContainer->Resolve<EngineCoreEventBus>(), m_diContainer->Resolve<ThreadSearchService>());
}

void WorldThreadWrapper::InvokeMemoryBarrier([[maybe_unused]] IClientThread *clientThread) {
    Fence fence(m_concurrencyFactory);
}