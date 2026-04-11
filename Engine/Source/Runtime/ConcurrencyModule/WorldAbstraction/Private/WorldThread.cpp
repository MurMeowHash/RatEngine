#include "WorldThread.h"
#include "InfiniteThreadContext.h"
#include "ProjectSettings/ProjectSettings.h"
#include "CommandProducerThreadContext.h"
#include "LinearAllocator.h"
#include "RenderCommand.h"
#include "FrameCommandSubmitSystem.h"
#include "DiContainer.h"
#include "FrameLagContext.h"
#include "RenderThread.h"
#include "FrameLagConstraintSystem.h"
#include "FrameIncrementSystem.h"

void WorldThread::InitializeContext() {
    ClientThreadWrapperBase::InitializeContext();

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

void WorldThread::OnThreadBegin() {
    ClientThreadWrapperBase::OnThreadBegin();

    m_threadProcessor->AddSystem<FrameCommandSubmitSystem<RenderCommand>>(m_diContainer->Resolve<EngineCoreEventBus>(),
            m_diContainer->Resolve<ThreadSearchService>(), m_diContainer->Resolve<CommandThreadStorage>());

    m_threadProcessor->AddSystem<FrameLagConstraintSystem<WorldThread, RenderThread>>(m_diContainer->Resolve<ThreadSearchService>(),
        m_diContainer->Resolve<EngineCoreEventBus>());

    m_threadProcessor->AddSystem<FrameIncrementSystem>(m_diContainer->Resolve<EngineCoreEventBus>(), m_diContainer->Resolve<ThreadSearchService>());

    m_engineCoreEventBus->Subscribe<EngineCoreEvents::EngineBeginFrameEvent>(m_engineBeginFrameCallback);
}

void WorldThread::OnThreadEnd() {
    ClientThreadWrapperBase::OnThreadEnd();
    m_engineCoreEventBus->UnSubscribe<EngineCoreEvents::EngineBeginFrameEvent>(m_engineBeginFrameCallback);
}

WorldThread::WorldThread(IPlatformInteractor* platformInteractor, ThreadStorage* threadStorage, IConcurrencyFactory* concurrencyFactory,
                         EngineCoreEventBus* engineCoreEventBus, ProjectSettings* projectSettings, DiContainer* diContainer)
: ClientThreadWrapperBase(platformInteractor, threadStorage, concurrencyFactory, engineCoreEventBus), m_projectSettings(projectSettings),
m_diContainer(diContainer) {
    m_commandBufferAllocator = new LinearAllocator(m_projectSettings->GetMemoryAllocationSettings().m_commandBufferChunkSize);
    m_engineBeginFrameCallback = new ObjectDelegate<WorldThread, const EngineCoreEvents::EngineBeginFrameEvent&>(this, &WorldThread::OnEngineBeginFrame);
}

WorldThread::~WorldThread() {
    m_commandBufferAllocator->FreeMemory();
    delete m_commandBufferAllocator;
    delete m_engineBeginFrameCallback;
}

void WorldThread::OnEngineBeginFrame(const EngineCoreEvents::EngineBeginFrameEvent &beginFrameEventData) {
    if (beginFrameEventData.m_threadId != GetThreadId())
        return;

    m_threadProcessor->Tick();
}